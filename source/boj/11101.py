import sys
input = lambda: sys.stdin.readline().strip()

def __main__():
    t = int(input())
    for _ in range(t):
        costs_list = input().split(',')
        for i in range(len(costs_list)):
            costs_list[i] = costs_list[i].split(':')
            costs_list[i][1] = int(costs_list[i][1])
        costs = dict(costs_list)

        conditions = input().split('|')
        for i in range(len(conditions)):
            conditions[i] = conditions[i].split('&')

        ans = 1e18
        
        for i, condition in enumerate(conditions):
            cur_cost = 0
            for sub_condition in condition:
                cur_cost = max(cur_cost, costs[sub_condition])
            ans = min(ans, cur_cost)

        print(ans)

if __name__ == "__main__":
    __main__()
