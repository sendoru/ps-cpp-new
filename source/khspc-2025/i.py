from collections import defaultdict
OFFSET = int(1e6) + 1

# dp[i][j][k] 길이 i, 연산자 위치가 j인 수식 중 값이 k인 경우의 수

dp = [{} for _ in range(7)]

def solve():
    # n = val, m = len
    n, m = map(int, input().split())

    chars = "0123456789+-"

    for i in range(1, 7):
        # generate all combinations of digits and operators
        def sub(s, idx, op_pos):
            # filter trailng zeros
            if len(s) == 2 and s[-1] not in "+-" and s[-2] == '0':
                return
            if len(s) > 2 and s[-1] not in "+-" and s[-2] == '0' and s[-3] in "+-":
                return
            
            # leading/duplicate operators
            if len(s) == 1 and s[0] in "+-":
                return
            if len(s) >= 2 and s[-1] in "+-" and s[-2] in "+-":
                return
            
            if idx == i:
                if s[-1] in "+-":
                    return
                # calculate the value of the expression
                value = 0
                cur = 0
                sign = 1  # 1 for +, -1 for -
                for c in s:
                    if c.isdigit():
                        cur = cur * 10 + int(c)
                    else:
                        value += sign * cur
                        cur = 0
                        sign = 1 if c == '+' else -1
                value += sign * cur
                if -OFFSET <= value <= OFFSET:
                    if not tuple(op_pos) in dp[i]:
                        dp[i][tuple(op_pos)] = [0] * (2 * OFFSET + 1)
                    dp[i][tuple(op_pos)][value + OFFSET] += 1
                return
            
            for c in chars:
                next_op_pos = op_pos[:]
                if c in "+-":
                    next_op_pos.append(idx)
                sub(s + c, idx + 1, next_op_pos)

        sub("", 0, [])

    if m <= 6:
        res = 0
        for op_pos in dp[m]:
            res += dp[m][op_pos][n + OFFSET]
        return res
    
    # mitm
    res = 0
    op_poses = set()
    for l_len in range(1, 7):
        r_len = m - l_len - 1
        if r_len < 1 or r_len > 6:
            continue
        for l_op_pos in dp[l_len]:
            for r_op_pos in dp[r_len]:
                full_op_pos = list(l_op_pos) + [l_len]
                for op in r_op_pos:
                    full_op_pos.append(op + l_len + 1)
                if tuple(full_op_pos) in op_poses:
                    continue
                op_poses.add(tuple(full_op_pos))
                for left_val in range(-OFFSET // 5, OFFSET // 5 + 1):
                    # plus
                    right_val = n - left_val
                    if -OFFSET <= right_val <= OFFSET:
                        res += dp[l_len][l_op_pos][left_val + OFFSET] * dp[r_len][r_op_pos][right_val + OFFSET]
                    # minus
                    right_val = left_val - n
                    if -OFFSET <= right_val <= OFFSET:
                        res += dp[l_len][l_op_pos][left_val + OFFSET] * dp[r_len][r_op_pos][right_val + OFFSET]
                res %= (int(1e9) + 7)

    for l_len in range(1, 4):
        for r_len in range(1, 4):
            if l_len + r_len + 2 >= m:
                continue
            # l op mid op r
            # where mid is a single number
            mid_len = m - l_len - r_len - 2
            l_range = range(-int(pow(10, l_len - 1)), int(pow(10, l_len)))
            r_range = range(-int(pow(10, r_len - 1)), int(pow(10, r_len)))

            for l_op_pos in dp[l_len]:
                for r_op_pos in dp[r_len]:
                    full_op_pos = list(l_op_pos) + [l_len, l_len + mid_len + 1]
                    for op in r_op_pos:
                        full_op_pos.append(op + l_len + mid_len + 2)
                    if tuple(full_op_pos) in op_poses:
                        continue
                    op_poses.add(tuple(full_op_pos))

                    for l_val in l_range:
                        for r_val in r_range:
                            # l + mid + r
                            mid = n - l_val - r_val
                            if len(str(mid)) == mid_len and mid >= 0:
                                res += dp[l_len][l_op_pos][l_val + OFFSET] * dp[r_len][r_op_pos][r_val + OFFSET]

                            # l - mid + r
                            mid = -n + l_val + r_val
                            if len(str(mid)) == mid_len and mid >= 0:
                                res += dp[l_len][l_op_pos][l_val + OFFSET] * dp[r_len][r_op_pos][r_val + OFFSET]

                            # l + mid - r
                            mid = n - l_val + r_val
                            if len(str(mid)) == mid_len and mid >= 0:
                                res += dp[l_len][l_op_pos][l_val + OFFSET] * dp[r_len][r_op_pos][r_val + OFFSET]

                            # l - mid - r
                            mid = l_val - r_val - n
                            if len(str(mid)) == mid_len and mid >= 0:
                                res += dp[l_len][l_op_pos][l_val + OFFSET] * dp[r_len][r_op_pos][r_val + OFFSET]
                            
                    res %= (int(1e9) + 7)

    return res % (int(1e9) + 7)

if __name__ == "__main__":
    print(solve())
