n, k = map(int, input().split())
a = list(map(int, input().split()))
cur = 1
for elem in a:
    cur = cur * elem
    if len(str(cur)) > k:
        cur = 1

print(cur)