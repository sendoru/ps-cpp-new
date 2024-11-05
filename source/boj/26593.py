from decimal import Decimal
import decimal
decimal.getcontext().prec = 100


def main():
    l = []
    while True:
        try:
            a, b, c = input().split()
            b = int(b)
            c1, c2 = c.split('.')
            assert (len(c2) == 2)
            c = Decimal(c)
            c *= b
            l.append((a, b, c))
        except EOFError:
            break
    l.sort(key=lambda x: (-x[2], -x[1], x[0]))
    for a, b, c in l:
        print(f"${c:.2f} - {a}/{b}")


if __name__ == '__main__':
    main()
