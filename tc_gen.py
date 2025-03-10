import random


def gen_random_tree_edges(n):
    parents = [-1 for i in range(n)]
    for i in range(1, n):
        parents[i] = random.randint(0, i - 1)

    edges = []
    for i in range(1, n):
        edges.append((parents[i], i))

    return edges


def gen_tc(n, k):
    edges = gen_random_tree_edges(n)
    print(n, k)
    for edge in edges:
        print(edge[0] + 1, edge[1] + 1)


def main():
    n = 5000
    k = random.randint(1, int(1e12))
    gen_tc(n, k)


if __name__ == '__main__':
    main()
