from math import gcd
from fractions import Fraction
import sys
input = lambda: sys.stdin.readline().strip()

comb = [[0] * 28 for _ in range(28)]
factorial = [1] * 28

def get_comb(n, k):
    if n < k:
        return 0
    if comb[n][k] != 0:
        return comb[n][k]
    if k == 0 or n == k:
        return 1
    comb[n][k] = get_comb(n - 1, k - 1) + get_comb(n - 1, k)
    return comb[n][k]

dp = []

def main():
    for i in range(2, 28):
        factorial[i] = factorial[i - 1] * i
    dp.append([Fraction(0)] * 27)
    dp[0][1] = Fraction(1)
    for i in range(1, 26):
        cur = [get_comb(i + 1, j) for j in range(27)]
        cur[0] = 0
        for j in range(i):
            sub = [get_comb(i + 1, j) * k for k in dp[j]]
            cur = [cur[k] - sub[k] for k in range(27)]
        dp.append(list(map(lambda x: Fraction(x, i + 1), cur)))

    t = int(input())
    for _ in range(t):
        nc = list(map(int, input().split()))
        n = nc[0]
        c = nc[1:]

        coeffs = [Fraction(0)] * 27
        for i in range(n + 1):
            for j in range(27):
                coeffs[j] += c[i] * dp[i][j]

        ans = 0
        for i in range(27):
            ans += abs(coeffs[i].as_integer_ratio()[0])

        ans += abs(c[0])
        print(ans)


if __name__ == "__main__":
    main()

