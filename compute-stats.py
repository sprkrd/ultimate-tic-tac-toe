#!/usr/bin/env python3

from tqdm import tqdm

from subprocess import check_output
from sys import argv

from os.path import splitext, basename

def stats_str(N, program1, program2, wins):
    program1 = splitext(basename(program1))[0]
    program2 = splitext(basename(program2))[0]
    return "Wins {} / Ties / Wins {}: {:.02%} / {:.02%} / {:.02%}".format(
            program1, program2, wins[0]/N, (N-sum(wins))/N, wins[1]/N)


def main():
    program1 = argv[1]
    program2 = argv[2]

    N = int(argv[3])
    wins = [0, 0]

    cmd1 = ("./server-9x9.x", program1, program2)
    cmd2 = ("./server-9x9.x", program2, program1)

    cmds = (cmd1, cmd2)

    for idx in tqdm(range(N)):
        cmd_idx = idx%2
        out = check_output(cmds[cmd_idx]).decode().strip()
        if out == "Player 0 (x) WINS!":
            wins[cmd_idx] += 1
        elif out == "Player 1 (o) WINS!":
            wins[1-cmd_idx] += 1
        tqdm.write(stats_str(idx+1,program1,program2,wins))

    # print(stats_str(N, program1, program2, wins))


if __name__ == "__main__":
    main()

