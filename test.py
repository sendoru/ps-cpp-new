def check(ls, queries):
    ls = ls.copy()
    ls_max = max(ls)
    ls_min = min(ls)
    q = len(queries)
    for i in range(q):
        op, a, b = queries[i]
        if op == 1:
            to_be = min(ls[a-1:b])
            for j in range(a-1, b):
                ls[j] = to_be
        else:
            to_be = max(ls[a-1:b])
            for j in range(a-1, b):
                ls[j] = to_be

    cnts = dict()
    for i in ls:
        if i in cnts:
            cnts[i] += 1
        else:
            cnts[i] = 1
        if i != ls_max and i != ls_min:
            print("Error: unexpected value in ls")
            print(ls_max, ls_min)
            print(*ls)
            return False
    if len(cnts) == 2:
        if abs(cnts[ls_max] - cnts[ls_min]) > 1:
            print("Error: abs(cnts[ls_max] - cnts[ls_min]) > 1")
            print(ls_max, ls_min)
            print(*ls)
            return False
    
    return True

def main():
    tc_file = open("tc.txt", "r")
    output_file = open("output.txt", "r")
    T = int(tc_file.readline())
    failed_cases = []
    for t in range(T):
        n = int(tc_file.readline())
        ls = list(map(int, tc_file.readline().split()))
        __ = output_file.readline()
        q = int(output_file.readline())
        queries = []
        for _ in range(q):
            queries.append(list(map(int, output_file.readline().split())))
        # print("Test case", t+1)
        if check(ls, queries):
            pass
            # print("Passed")
        else:
            print(*ls)
            print(len(ls))
            failed_cases.append(t+1)
            

    print("-"*30)
    print(f"Failed cases count: {len(failed_cases)}")
    print(*failed_cases)

if __name__ == "__main__":
    main()
