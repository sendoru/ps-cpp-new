from decimal import Decimal, getcontext
import sys
getcontext().prec = 40
input = lambda: sys.stdin.readline().rstrip()

def main():
    n, b = input().split()
    n = int(n)
    b = Decimal(b)
    xy = [tuple(map(Decimal, input().split())) for _ in range(n)]

    lo = Decimal(-2e6)
    hi = Decimal(2e6)
    p4, p3, p2, p1 = 0, 0, 0, 0
    for x, y in xy:
        p4 += x ** 4
        p3 += -4 * x ** 3 * (y - b)
        p2 += 6 * x * x * (y - b) * (y - b)
        p1 += -4 * x * (y - b) * (y - b) * (y - b)
    for _ in range(100):
        mid = (lo + hi) / 2
        dmid = 4 * p4 * mid ** 3 + 3 * p3 * mid ** 2 + 2 * p2 * mid + p1
        if dmid > 0:
            hi = mid
        else:
            lo = mid
    print(f"{(lo + hi) / 2:.10f}")

if __name__ == '__main__':
    main()