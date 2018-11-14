#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <error.h>

#define ONGOING -1
#define TIE -2
#define N_PLAYERS 2

void usage(const char* executable) {
  error(1, 0, "Usage: %s path/to/player1 path/to/player2", executable);
}

void exec(const char* executable, int fd_in, int fd_out) {
  dup2(fd_in, 0);
  dup2(fd_out, 1);
  close(fd_in);
  close(fd_out);
  execlp(executable, executable, NULL);
  perror("bad exec");
  _exit(1);
}

void server(FILE* in[], FILE* out[]);

int main(int argc, char* argv[]) {
  int server_to_player[N_PLAYERS][2];
  int player_to_server[N_PLAYERS][2];
  FILE* in[N_PLAYERS];
  FILE* out[N_PLAYERS];
  int pid[N_PLAYERS];
  int idx, jdx;
  if (argc != 3) usage(argv[0]);
   
  for (idx = 0; idx < N_PLAYERS; ++idx) {
    if (pipe(server_to_player[idx]) == -1) {
      perror("bad pipe");
      return 1;
    }
    if (pipe(player_to_server[idx]) == -1) {
      perror("bad pipe");
      return 1;
    }
  }

  for (idx = 0; idx < N_PLAYERS; ++idx) {
    printf("Forking and executing %s...\n", argv[1+idx]);
    pid[idx] = fork();
    if (pid[idx] == -1) {
      /* parent process: fail */
      perror("bad fork");
      return 1;
    } else if (pid[idx] == 0) {
      /* child process */
      close(server_to_player[idx][1]); /* close write end of server_to_player pipe */
      close(player_to_server[idx][0]); /* close read end of player_to_server pipe */
      for (jdx = 0; jdx < N_PLAYERS; ++jdx) {
        /* close all the irrelevant pipes */
        if (jdx == idx) continue;
        close(server_to_player[jdx][0]);
        close(server_to_player[jdx][1]);
        close(player_to_server[jdx][0]);
        close(player_to_server[jdx][1]);
      }
      /* mutate child process into client */
      exec(argv[1+idx], server_to_player[idx][0], player_to_server[idx][1]);
    } else {
      /* parent process */
      close(server_to_player[idx][0]); /* close read end of server_to_player pipe */
      close(player_to_server[idx][1]); /* close write end of player_to_server pipe */
      /* create stream for each process' pipes */
      out[idx] = fdopen(server_to_player[idx][1], "w");
      in[idx] = fdopen(player_to_server[idx][0], "r");
    }
  }

  server(in, out);

  /* Terminate children */
  for (idx = 0; idx < 2; ++idx) {
    kill(pid[idx], SIGTERM);
  }

  return 0;
}

int lines[][3] = {
  {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

struct cell {
  int row;
  int col;
};

struct game {
  char board[9][9];
  char status_3x3[3][3];
  struct cell last_filled;
  struct cell active_3x3;
  int turn;
  int current_player;
  int winner;
};

void init_game(struct game* game) {
  memset(game->board, ' ', sizeof(game->board));
  memset(game->status_3x3, ' ', sizeof(game->status_3x3));
  game->last_filled.row = -1;
  game->last_filled.col = -1;
  game->active_3x3.row = -1;
  game->active_3x3.col = -1;
  game->turn = 0;
  game->current_player = 0;
  game->winner = ONGOING;
}

void extract_subboard(const char* board, char* subboard,
    const struct cell* target_3x3) {
  int idx, jdx, idx_, jdx_;
  for (idx = 0; idx < 3; ++idx) {
    for (jdx = 0; jdx < 3; ++jdx) {
      idx_ = 3*target_3x3->row + idx;
      jdx_ = 3*target_3x3->col + jdx;
      subboard[3*idx+jdx] = board[9*idx_+jdx_];
    }
  }
}

int check_winner(const char* board) {
  int winner = TIE;
  int idx;
  for (idx = 0; idx < 8; ++idx) {
    char first = board[lines[idx][0]];
    char second = board[lines[idx][1]];
    char third = board[lines[idx][2]];
    if ((first == 'x' || first == 'o') && first == second && first == third) {
      winner = first == 'x'? 0 : 1;
      break;
    }
  }
  if (winner == TIE) {
    for (idx = 0; idx < 9; ++idx) {
      if (board[idx] == ' ') {
        winner = ONGOING;
        break;
      }
    }
  }
  return winner;
}

int get_available_cells(struct cell empty[], const struct game* game) {
  int count_empty = 0;
  int row_min, row_max, col_min, col_max, row, col;
  if (game->active_3x3.row == -1) {
    row_min = col_min = 0;
    row_max = col_max = 9;
  } else {
    row_min = 3*game->active_3x3.row;
    row_max = row_min + 3;
    col_min = 3*game->active_3x3.col;
    col_max = col_min + 3;
  }
  for (row = row_min; row < row_max; ++row) {
    for (col = col_min; col < col_max; ++col) {
      if (game->board[row][col] == ' ' && game->status_3x3[row/3][col/3] == ' ') {
        empty[count_empty].row = row;
        empty[count_empty].col = col;
        ++count_empty;
      }
    }
  }
  return count_empty;
}

void play_next_move(struct game* game, FILE* in) {
  struct cell input, target_3x3, next_3x3;
  char subboard[3][3];
  int local_winner, read;
  int ok = 1;
  read = fscanf(in, "%d %d", &input.row, &input.col);
  /* Check bad format */
  if (read != 2) {
    if (read == EOF) error(0,0,"EOF");
    else perror("bad scanf");
    ok = 0;
  }
  /* Check bad range */
  if (ok && (input.row < 0 || input.row > 8 || input.col < 0 || input.col > 8)) {
    error(0, 0, "Not in range: %d %d", input.row, input.col);
    ok = 0;
  }
  /* Check non-active 3x3 */
  target_3x3.row = input.row / 3;
  target_3x3.col = input.col / 3;
  if (ok && !( game->active_3x3.row == -1 ||
      (game->active_3x3.row == target_3x3.row &&
       game->active_3x3.col == target_3x3.col) )) {
    error(0, 0, "Bad input: %d %d. Active 3x3 is %d %d. "
          "Target 3x3 is %d %d", input.row, input.col,
          game->active_3x3.row, game->active_3x3.col,
          target_3x3.row, target_3x3.col);
    ok = 0;
  }
  /* Check non-empty */
  if (ok && game->board[input.row][input.col] != ' ') {
    error(0, 0, "Position %d %d is not empty", input.row, input.col);
    ok = 0;
  }
  /* Check target area status */
  if (ok && game->status_3x3[target_3x3.row][target_3x3.col] != ' ') {
    error(0, 0, "Target area %d %d is not playable",
        target_3x3.row, target_3x3.col);
    ok = 0;
  }
  if (ok) {
    /* All good! The movement can be safely played */
    game->board[input.row][input.col] = "xo"[game->current_player];
    game->last_filled = input;
    extract_subboard((const char*)game->board, (char*)subboard, &target_3x3);
    local_winner = check_winner((const char*)subboard);
    if (local_winner >= 0) {
      /* Either player 1 or player 2 won this sub-board */
      game->status_3x3[target_3x3.row][target_3x3.col] = "xo"[local_winner];
    } else if (local_winner == TIE) {
      /* Full sub-board */
      game->status_3x3[target_3x3.row][target_3x3.col] = 'F';
    }
    if (local_winner != ONGOING) {
      /* sub-board has a winner or either was completely filled, check
       * global game */
      game->winner = check_winner((const char*)game->status_3x3);
    }
    if (game->winner == ONGOING) {
      next_3x3.row = input.row % 3;
      next_3x3.col = input.col % 3;
      if (game->status_3x3[next_3x3.row][next_3x3.col] != ' ') {
        /* Area is not playable, player can play wherever he wants */
        next_3x3.row = next_3x3.col = -1;
      }
      game->active_3x3 = next_3x3;
      game->current_player = 1 - game->current_player;
    }
  }
  else {
    /* Current player movement is not conformant with the rules, the
     * opponent wins */
    game->winner = 1 - game->current_player;
  }
  game->turn += 1;
}

void send_game_info(const struct game* game, FILE* out) {
  int idx, count_available;
  struct cell available[81];
  count_available = get_available_cells(available, game);
  fprintf(out, "%d %d\n%d\n",
      game->last_filled.row, game->last_filled.col, count_available);
  for (idx = 0; idx < count_available; ++idx) {
    fprintf(out, "%d %d\n", available[idx].row, available[idx].col);
  }
  fflush(out);
}

void print_large_board(char board[][9]) {
  int idx;
  for (idx = 0; idx < 9; ++idx) {
    if (idx % 3 == 0) {
      printf("             |             |             \n");
    }
    printf("  %c | %c | %c  |  %c | %c | %c  |  %c | %c | %c  \n",
        board[idx][0], board[idx][1], board[idx][2],
        board[idx][3], board[idx][4], board[idx][5],
        board[idx][6], board[idx][7], board[idx][8]);
    if (idx % 3 < 2) {
      printf(" ---|---|--- | ---|---|--- | ---|---|--- \n");
    } else {
      printf("             |             |             \n");
      if (idx != 8) {
        printf("-------------|-------------|-------------\n");
      }
    }
  }
}

void print_small_board(char board[][3]) {
  printf(" %c | %c | %c\n", board[0][0],board[0][1], board[0][2]);
  printf("---|---|---\n");
  printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
  printf("---|---|---\n");
  printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

void show_game(struct game* game) {
  printf("---------------- Turn %2d ----------------\n", game->turn);
  printf("Board:\n");
  print_large_board(game->board);
  printf("3x3 blocks' status:\n");
  print_small_board(game->status_3x3);
  printf("Last filled: %d %d\n", game->last_filled.row, game->last_filled.col);
  printf("Active 3x3 block: %d %d\n", game->active_3x3.row, game->active_3x3.col);
  printf("Current player: %d\n", game->current_player);
}

void server(FILE* in[], FILE* out[]) {
  struct game game;
  init_game(&game);
  show_game(&game);
  while (game.winner==ONGOING) {
    send_game_info(&game, out[game.current_player]);
    play_next_move(&game, in[game.current_player]);
    show_game(&game);
  }
  if (game.winner == TIE) {
    printf("Game ends in a TIE!\n");
  } else {
    printf("Player %d (%c) WINS!\n", game.winner, "xo"[game.winner]);
  }
}

