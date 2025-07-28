n = int(input())
algos = []
for _ in range(n):
    name, diff = input().split()
    algos.append((name, int(diff)))
m = int(input())
ppl = {}
for _ in range(m):
    name, level = input().split()
    ppl[name] = int(level)
q = int(input())
cur_ppl = ""
for _ in range(q):
    query = input().split()
    if query[-1] == "chan!":
        cur_ppl = query[0]
        print("hai!")
    else:
        level_diff = []
        for name, diff in algos:
            level_diff.append((abs(ppl[cur_ppl] - diff), name))
        level_diff.sort()
        print(f"{level_diff[1][1]} yori mo {level_diff[0][1]}")