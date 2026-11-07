#!/usr/bin/env python3
import random
from pwn import *

n = 100
poses_encoded = random.sample(range(40000), 100)
board = [[0] * 200 for _ in range(200)]
for pos in poses_encoded:
    x = pos // 200
    y = pos % 200
    board[x][y] = 1

ans = 2 * n
for i in range(200):
    if sum(board[i]) > 0:
        ans -= 1
for j in range(200):
    if sum(board[i][j] for i in range(200)) > 0:
        ans -= 1

p = process(['source/anime_cup_3/ep10'])
query_cnt = 0

p.sendline(str(n).encode())

while True:
    query = p.recvline().decode().strip().split()
    if (query[0] == '?'):
        query_cnt += 1
        if query_cnt > 3 * n:
            p.sendline(b"-1")
            print("WA: too many queries")
            break
        x1 = int(query[1]) - 1
        y1 = int(query[2]) - 1
        x2 = int(query[3]) - 1
        y2 = int(query[4]) - 1
        range_sum = 0
        for i in range(x1, x2 + 1):
            for j in range(y1, y2 + 1):
                range_sum += board[i][j]
        p.sendline(str(range_sum).encode())
    elif (query[0] == '!'):
        if int(query[1]) == ans:
            print("AC")
        else:
            print("WA")
        break
