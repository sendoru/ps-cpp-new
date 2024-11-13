def divide_line(s: list[str], expcted_line_digit: int) -> list[str]:
    idx = 0
    cur_len = 0
    cur_line = 1
    ans = [[]]

    while idx < len(s):
        if cur_len + len(s[idx]) + 4 + len(str(cur_line)) + expcted_line_digit > 280:
            cur_line += 1
            cur_len = 0
            ans.append([])
        else:
            cur_len += len(s[idx]) + 1
            ans[-1].append(s[idx])
            idx += 1
    return ans


def __main__():
    n = int(input())
    ss = [input() for _ in range(n)]
    ss = map(lambda s: ' '.join(s.split()[:-1]), ss)
    s = ' '.join(ss)
    ss = s.split()

    ans = divide_line(ss, len(str(n)))
    for i in range(len(str(n)) - 1, 0, -1):
        new_ans = divide_line(ss, i)
        if len(new_ans) < len(ans) and len(new_ans) <= 10 ** i - 1:
            ans = new_ans

    for i, line in enumerate(ans):
        ans[i].append(f'({i + 1}/{len(ans)})')
    ans = list(map(lambda x: ' '.join(x), ans))

    print(len(ans))
    for line in ans:
        print(line)


__main__()
