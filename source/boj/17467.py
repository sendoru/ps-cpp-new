n, p = map(int, input().split())
if n <= p // 2:
    ans = 1
    for i in range(2, n + 1):
        ans *= i
        ans %= p
    print(ans)
else:
    ans = 1
    # fact(p - 1) == p s- 1 == -1 mod p
    # fact(n) == fact(p - 1) / * ((p - 1) * (p - 2) * ... * (n + 1))
    # == -1 / ((p - 1) * (p - 2) * ... * (n + 1)) mod p
    for i in range(p - 1, n, -1):
        ans *= i
        ans %= p
    print(pow(-ans, -1, p))
