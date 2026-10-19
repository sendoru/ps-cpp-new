n = int(input())

ans = 0
fact = 2

for l in range(3, 21):
    fact *= l
    if fact > n:
        break

    a1_max = n ** (1 / l) + 2
    for a1 in range(1, int(a1_max) + 1):
        d1_l = 1
        d1_r = int(n ** (1 / (l - 1)) + 2)
        d1 = 1
        while d1_l <= d1_r:
            d1_mid = (d1_l + d1_r) // 2
            cur = a1
            prod = 1
            for i in range(l):
                prod *= cur
                cur += d1_mid
                if prod > n:
                    break
            if prod <= n:
                d1 = max(d1, d1_mid)
                d1_l = d1_mid + 1
            else:
                d1_r = d1_mid - 1
        ans += d1
print(ans)
