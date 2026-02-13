import os
import sys
from math import gcd
B = 20_000_000
pf_sum = [0] * (B + 1)

for i in range(2, 20000):
    for j in range(1, i):
        cur = 2 * i * i + 2 * i * j
        if cur > B:
            break
        if gcd(i, j) != 1 or (i + j) % 2 == 0:
            continue
        while cur <= B:
            pf_sum[cur] += 1
            cur += 2 * i * i + 2 * i * j

for i in range(1, B + 1):
    if pf_sum[i] > 1:
        pf_sum[i] = 0
    pf_sum[i] += pf_sum[i - 1]


def main():
    # open stdin as file descriptor 0
    s = os.fdopen(0).read().strip().split('\n')
    for n in s:
        print(pf_sum[int(n)])


if __name__ == '__main__':
    main()
