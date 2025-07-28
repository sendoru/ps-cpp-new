import sys
input = lambda: sys.stdin.readline().rstrip('\n')

T = int(input())
for _ in range(T):
    n = int(input())
    s = '+' + input()
    after_minus = False
    printed = False
    for i in range(0, len(s), 2):
        sign, num = s[i], int(s[i + 1])
        if after_minus and num != 0:
            print("NO")
            printed = True
            break
        after_minus |= (sign == '-')
    if not printed:
        print("YES")