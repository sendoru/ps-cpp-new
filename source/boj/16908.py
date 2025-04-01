import sys
import random
from collections import defaultdict

input = lambda: sys.stdin.readline().rstrip()

powers = [0] * 100010
HASH_BASE = random.choice([31, 37, 41, 73, 47, 53, 61, 67, 71, 73, 79, 83, 89])
HASH_MOD = random.choice([1e9 + 3, 1e9 + 39, 1e9 + 61, 1e9 + 63])
def hash_push_back(h, x):
    return (h * HASH_BASE + x) % HASH_MOD

def hash_pop_front(h, x, l):
    return (h - x * powers[l - 1]) % HASH_MOD

def get_unique_substring_hashs(s, length, ret: set):
    if length > len(s):
        return set()
    h = 0
    for i in range(length):
        h = hash_push_back(h, ord(s[i]))
    ret.add(h)
    for i in range(length, len(s)):
        h = hash_pop_front(h, ord(s[i - length]), length)
        h = hash_push_back(h, ord(s[i]))
        ret.add(h)

def main():
    global powers
    powers[0] = 1
    for i in range(1, 100010):
        powers[i] = (powers[i - 1] * HASH_BASE) % HASH_MOD

    n = int(input())
    a = [input() for _ in range(n)]
    lo = 0
    hi = min(len(s) for s in a)
    ans = 0

    while lo <= hi:
        mid = (lo + hi) // 2
        if mid == 0:
            break
        hashs = [set() for _ in range(n)]
        for i in range(n):
            get_unique_substring_hashs(a[i], mid, hashs[i])
        cnt = defaultdict(int)
        max_cnt = 0
        for i in range(n):
            for h in hashs[i]:
                cnt[h] += 1
                max_cnt = max(max_cnt, cnt[h])

        if max_cnt == n:
            ans = max(ans, mid)
            lo = mid + 1
        else:
            hi = mid - 1
    print(ans)

if __name__ == "__main__":
    main()
