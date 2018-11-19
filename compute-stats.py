#!/usr/bin/env python3

from subprocess import check_output
from sys import argv
from tqdm import tqdm

program1 = argv[1]
program2 = argv[2]

N = 20
wins_x = 0
loses_x = 0

cmd = ("./server-9x9.x", program1, program2)

for _ in tqdm(range(N)):
    out = check_output(cmd).decode().strip()
    if out == "Player 0 (x) WINS!":
        wins_x += 1
    elif out == "Player 1 (o) WINS!":
        loses_x += 1

print("Wins (%) / Ties (%) / Loses (%): {:.02f}% / {:.02f}% / {:.02f}%".format(
        wins_x/N*100,(N-wins_x-loses_x)/N*100,loses_x/N*100))

