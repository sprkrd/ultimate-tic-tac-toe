#include <iostream>
#include <random>
#include <chrono>
#include <vector>
using namespace std;

default_random_engine rng;

struct Action {
  int row, col;
};

int main() {
  rng.seed(chrono::system_clock::now().time_since_epoch().count());
  while (true) {
    int opponent_row, opponent_col;
    cin >> opponent_row >> opponent_col;
    int valid_action_count;
    cin >> valid_action_count;
    vector<Action> available_actions(valid_action_count);
    for (int idx = 0; idx < valid_action_count; ++idx) {
      cin >> available_actions[idx].row >> available_actions[idx].col;
    }
    const Action& choice = available_actions[rng()%valid_action_count];
    cout << choice.row << ' ' << choice.col << endl;
  }
}

