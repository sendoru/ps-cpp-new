def main():
    n = int(input())
    s1 = input()
    s2 = input()

    if s1 == "1" * n:
        tmp = s2.count("1")
        print(1 + tmp * (tmp - 1))

    elif s1 == "0" * n:
        print(0)

    else:
        s1 = (s1 + s1[0])[1:]
        zero_idx = s1.find("0")
        s1 = s1[zero_idx:] + s1[:zero_idx] + "0"
        s2 = s2[zero_idx:] + s2[:zero_idx] + s2[zero_idx]

        idx = s1.find("1")
        is_cur_one = True
        one_intervals = []

        s2_prefix_sum = [0] * len(s2)
        s2_prefix_sum[0] = int(s2[0])
        for i in range(1, len(s2)):
            s2_prefix_sum[i] = s2_prefix_sum[i - 1] + int(s2[i])

        for i in range(idx, len(s1)):
            if is_cur_one and s1[i] == "0":
                is_cur_one = False
                one_intervals.append([idx, i - 1])
            elif not is_cur_one and s1[i] == "1":
                is_cur_one = True
                idx = i

        ans = 0
        for interval in one_intervals:
            line_cnt = s2_prefix_sum[interval[1] +
                                     1] - s2_prefix_sum[interval[0] - 1]
            ans += line_cnt * (line_cnt - 1) // 2

        print(ans)


if __name__ == "__main__":
    main()
