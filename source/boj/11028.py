import os
import sys
from math import gcd
BOUND = 20_000_000
pf_sum = [0] * (BOUND + 1)

for i in range(2, 20000):
    for j in range(1, i):
        cur = 2 * i * i + 2 * i * j
        if cur > BOUND:
            break
        if gcd(i, j) != 1 or (i + j) % 2 == 0:
            continue
        while cur <= BOUND:
            pf_sum[cur] += 1
            cur += 2 * i * i + 2 * i * j

for i in range(1, BOUND + 1):
    if pf_sum[i] > 1:
        pf_sum[i] = 0
    pf_sum[i] += pf_sum[i - 1]


def main():
    # open stdin as file descriptor 0
    input_file = os.fdopen(0)
    input_text = input_file.read()
    assert input_text[-1] == '\n'
    input_lines = input_text.strip().split('\n')
    for line in input_lines:
        n = int(line)
        print(pf_sum[n])


if __name__ == '__main__':
    main()
