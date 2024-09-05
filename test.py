actions = {
    'S': 10,
    'Q': 5,
    'A': 7,
    'L': -8,
    'F': 4,
    'D': -5,
    'E': -10
}


def main():
    n = int(input())
    scores = {}
    names = {}
    for i in range(n):
        tmp = input().split()
        names[int(tmp[0]) - 1] = ' '.join(tmp[1:])
        scores[int(tmp[0]) - 1] = 0
    names = sorted(names.items())
    names = dict(names)

    m = int(input())
    for i in range(m):
        idx, action = input().split()
        idx = int(idx) - 1
        scores[idx] += actions[action]

    scores = sorted(scores.items())
    scores = dict(scores)

    by_score = {}
    for i in scores.keys():
        if scores[i] not in by_score:
            by_score[scores[i]] = []
        by_score[scores[i]].append(names[i])

    by_score = sorted(by_score.items(), reverse=True)
    print(*([by_score[0][0]] + by_score[0][1]))
    print(*([by_score[-1][0]] + by_score[-1][1]))


if __name__ == '__main__':
    main()
