import sys
input = lambda: sys.stdin.readline().rstrip('\n')

n, m = tuple(map(int, input().split()))
if (n, m) == (1, 1):
    print(-1)
elif n == 1:
    if m == 2:
        print(3)
        print(1, 4)
    else:
        a = [m]
        b = [i + 1 for i in range(m)]
        b[-1] = int(1e9)
        print(*a)
        print(*b)
else:
    a = [i + 1 for i in range(n)]
    b = [i + n + 1 for i in range(m)]
    a[-1] = int(1e9)
    print(*a)
    print(*b)