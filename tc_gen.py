import random

T = 1000
print(3 * T)
for _ in range(T):
    n = random.randint(3, 50)
    ls = [random.randint(1, 1000) for _ in range(n)]
    print(n)
    print(*ls)

for _ in range(T):
    n = random.randint(3, 30)
    ls = [random.randint(1, 5) for _ in range(n)]
    print(n)
    print(*ls)

for _ in range(T):
    n = random.randint(3, 15)
    ls = [random.randint(1, 2) for _ in range(n)]
    print(n)
    print(*ls)