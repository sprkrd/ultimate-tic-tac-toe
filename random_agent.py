#!/usr/bin/env python3

import random

while True:
    actions = []
    opponent_row, opponent_col = [int(i) for i in input().split()]
    valid_action_count = int(input())
    for i in range(valid_action_count):
        actions.append([int(j) for j in input().split()])

    print("{} {}".format(*random.choice(actions)))

