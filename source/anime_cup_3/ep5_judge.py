#!/usr/bin/env python3
import random
from pwn import *

n = random.randint(600, 670)
b = 0
p = process(['source/anime_cup_3/ep5'])
while True:
    if n < 0:
        p.sendline(b"-1")
        print("WA")
        break
    if n == 0:
        p.sendline(b"-1")
        print("AC")
        break
    if b != 0:
        x = b
    else:
        mod14 = n % 14
        if mod14 == 0:
            x = random.randint(1, 13)
        else:
            x = mod14
    p.sendline(str(x).encode())
    n -= x
    a, b = map(int, p.recvline().decode().strip().split())
    n -= a
