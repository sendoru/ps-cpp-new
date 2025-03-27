def solve():
    n = 150

    ans = [['.' for j in range(n)] for i in range(n)]

    for i in range(12):
        for j in range(i, n, 12):
            ans[i][j] = 'O'

    for i in range(12, 12+11):
        for j in range(0, i + 11*11, 11):
            ans[i][j] = 'O'

    for i in range(12+11, 12+11+10):
        for j in range(0, i + 10*10, 10):
            ans[i][j] = 'O'

    for i in range(12+11+10, 12+11+10+9):
        for j in range(0, i + 9*9, 9):
            ans[i][j] = 'O'

    for i in range(12+11+10+9, 12+11+10+9+8):
        for j in range(0, i + 8*8, 8):
            ans[i][j] = 'O'

    for i in range(12+11+10+9+8, 12+11+10+9+8+7):
        for j in range(0, i + 7*7, 7):
            ans[i][j] = 'O'

    for i in range(12+11+10+9+8+7, 12+11+10+9+8+7+6):
        for j in range(0, i + 6*6, 6):
            ans[i][j] = 'O'

    for i in range(12+11+10+9+8+7+6, 12+11+10+9+8+7+6+5):
        for j in range(0, i + 5*5, 5):
            ans[i][j] = 'O'

    for i in range(12+11+10+9+8+7+6+5, 12+11+10+9+8+7+6+5+4):
        for j in range(0, i + 4*4, 4):
            ans[i][j] = 'O'

    for i in range(12+11+10+9+8+7+6+5+4, 12+11+10+9+8+7+6+5+4+3):
        for j in range(0, i + 3*3, 3):
            ans[i][j] = 'O'

    # o_cnt = 0
    # for row in ans:
    #     o_cnt += row.count('O')
    # if o_cnt < 1700:
    #     return False

    return ans


def check(arr):
    n = len(arr)
    for r1 in range(n):
        for c1 in range(n):
            for r2 in range(r1 + 1, n):
                for c2 in range(c1 + 1, n):
                    if arr[r1][c1] == arr[r2][c2] == arr[r1][c2] == arr[r2][c1] == 'O':
                        return False

    o_cnt = 0
    for row in arr:
        o_cnt += row.count('O')
    if o_cnt < 1700:
        return False

    return True


def main():
    ans = solve()
    assert check(ans)
    for i in range(150):
        print(''.join(ans[i]))


if __name__ == '__main__':
    main()
