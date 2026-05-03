import sys
from collections import deque
def input(): return sys.stdin.readline().rstrip()


sys.setrecursionlimit(2 * 10**6)

MOD1 = 10**9 + 7


def modpow(a, b, m):
    res = 1
    a = a % m
    while b > 0:
        if b & 1:
            res = (res * a) % m
        a = (a * a) % m
        b >>= 1
    return res


def main():
    n, r = map(int, input().split())
    f = [-1] * n
    adj = [[] for _ in range(n)]
    f = list(map(lambda x: int(x) - 1, input().split()))
    for s in range(n):
        if s == f[s]:
            continue
        if s > f[s] and f[f[s]] == s:
            continue
        adj[s].append(f[s])
        adj[f[s]].append(s)

    dp = [0] * (n + 5)
    dp[3] = r * (r - 1) % MOD1
    cur = dp[3]
    for i in range(4, n + 1):
        cur = cur * (r - 1) % MOD1
        dp[i] = (cur - dp[i - 1]) % MOD1

    ans = 1
    visited = [False] * n
    for node in range(n):
        if visited[node]:
            continue
        visited[node] = True
        q = deque([(node, -1)])
        cc_size = 0
        has_cycle = False
        cycle_start = -1
        while q:
            cur, par = q.popleft()
            cc_size += 1
            for nxt in adj[cur]:
                if nxt == par:
                    continue
                if visited[nxt]:
                    has_cycle = True
                    cycle_start = nxt
                    continue
                visited[nxt] = True
                q.append((nxt, cur))

        if has_cycle:
            cycle_visited = set()
            cycle_size = 0

            # def dfs_cycle(cur, depth):
            #     nonlocal cycle_size
            #     nonlocal cycle_start
            #     nonlocal cycle_visited
            #     cycle_visited.add(cur)
            #     for nxt in adj[cur]:
            #         if nxt == cycle_start and depth > 1:
            #             cycle_size = depth + 1
            #             return
            #         if nxt in cycle_visited:
            #             continue
            #         dfs_cycle(nxt, depth + 1)
            # dfs_cycle(cycle_start, 0)

            dfs_stack = [(cycle_start, 0)]
            while dfs_stack:
                cur, depth = dfs_stack.pop()
                if cur in cycle_visited:
                    continue
                cycle_visited.add(cur)
                for nxt in adj[cur]:
                    if nxt == cycle_start and depth > 0:
                        cycle_size = depth + 1
                        break
                    if nxt in cycle_visited:
                        continue
                    dfs_stack.append((nxt, depth + 1))
            cycle_contrib = r * modpow(r - 1, cycle_size - 1, MOD1) % MOD1
            cycle_contrib = (cycle_contrib - dp[cycle_size]) % MOD1
            ans = ans * cycle_contrib % MOD1
            ans = ans * modpow(r - 1, cc_size - cycle_size, MOD1) % MOD1
        else:
            ans = ans * r % MOD1
            ans = ans * modpow(r - 1, cc_size - 1, MOD1) % MOD1
    print(ans)


if __name__ == '__main__':
    main()
