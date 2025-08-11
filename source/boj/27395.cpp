#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
const int MAX = 1'000'000;
using namespace std;
typedef long long ll;

int findRoot(int x, vector<int> &root) {
    if (root[x] == x)
        return x;
    return root[x] = findRoot(root[x], root);
}

bool hasSameRoots(int x, int y, vector<int> &root) {
    int xRoot = findRoot(x, root);
    int yRoot = findRoot(y, root);
    if (xRoot == yRoot)
        return true;
    else
        return false;
}

void unite(int x, int y, vector<int> &root, vector<int> &sizes) {
    int xRoot = findRoot(x, root);
    int yRoot = findRoot(y, root);
    if (xRoot != yRoot) {
        sizes[xRoot] += sizes[yRoot];
        root[yRoot] = xRoot;
    }
}

int getSize(int x, vector<int> &root, vector<int> &sizes) {
    int xRoot = findRoot(x, root);
    return sizes[xRoot];
}

void dfs(vector<vector<pair<int, int>>> &graph, vector<int> &parents, vector<int> &depths, vector<int> &costs, int curNode, int curDepth) {
    depths[curNode] = curDepth;
    for (auto next : graph[curNode]) {
        int nextNode = next.first, edgeCost = next.second;
        if (depths[nextNode] == -1) {
            parents[nextNode] = curNode;
            costs[nextNode] = edgeCost;
            dfs(graph, parents, depths, costs, nextNode, curDepth + 1);
        }
    }
}

void makeParentSparseTable(vector<vector<int>> &sparseTable, vector<int> &parents) {
    for (int i = 0; i < parents.size(); i++) {
        sparseTable[0][i] = parents[i];
    }
    for (int i = 1; i < sparseTable.size(); i++) {
        for (int j = 0; j < sparseTable[i].size(); j++) {
            sparseTable[i][j] = sparseTable[i - 1][sparseTable[i - 1][j]];
        }
    }
}

void makeMaxSparseTable(vector<vector<int>> &maxSparseTable, vector<vector<int>> &parentSparseTable, vector<int> &costs) {
    costs[0] = costs[1] = -MAX;
    for (int i = 0; i < costs.size(); i++) {
        maxSparseTable[0][i] = costs[i];
    }
    for (int i = 1; i < maxSparseTable.size(); i++) {
        for (int j = 0; j < maxSparseTable[i].size(); j++) {
            maxSparseTable[i][j] = max(maxSparseTable[i - 1][j], maxSparseTable[i - 1][parentSparseTable[i - 1][j]]);
        }
    }
}

int getLCA(vector<vector<int>> &sparseTable, vector<int> &depths, int u, int v) {
    if (depths[u] < depths[v])
        swap(u, v);
    int depthDiff = depths[u] - depths[v];
    for (int i = sparseTable.size() - 1; i >= 0; i--) {
        if (depthDiff & (1 << i)) {
            u = sparseTable[i][u];
        }
    }
    if (u == v) {
        return v;
    }
    for (int i = sparseTable.size() - 1; i >= 0; i--) {
        if (sparseTable[i][u] != sparseTable[i][v]) {
            u = sparseTable[i][u];
            v = sparseTable[i][v];
        }
    }
    return sparseTable[0][v];
}

int getMaxCost(vector<vector<int>> &parentSparseTable, vector<vector<int>> &maxSparseTable, vector<int> &depths, int u, int v) {
    int ret = -MAX;
    if (depths[u] < depths[v])
        swap(u, v);
    int depthDiff = depths[u] - depths[v];
    for (int i = parentSparseTable.size() - 1; i >= 0; i--) {
        if (depthDiff & (1 << i)) {
            ret = max(ret, maxSparseTable[i][u]);
            u = parentSparseTable[i][u];
        }
    }
    if (u == v) {
        return ret;
    }
    for (int i = parentSparseTable.size() - 1; i >= 0; i--) {
        if (parentSparseTable[i][u] != parentSparseTable[i][v]) {
            ret = max(ret, maxSparseTable[i][u]);
            ret = max(ret, maxSparseTable[i][v]);
            u = parentSparseTable[i][u];
            v = parentSparseTable[i][v];
        }
    }

    ret = max(ret, maxSparseTable[0][u]);
    ret = max(ret, maxSparseTable[0][v]);
    return ret;
}

struct Edge {
    int s = 0, e = 0, cost = 0;
    const bool operator<(const Edge &other) { return cost < other.cost; }
    const bool operator>(const Edge &other) { return cost > other.cost; }
};

struct Query {
    int idx = 0, x = 0, y = 0, minCost = 2 * MAX, reachableCnt = 0;
    const bool operator<(const Query &other) { return idx < other.idx; }
    const bool operator>(const Query &other) { return idx > other.idx; }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> edges(m);
    vector<int> roots(n + 1);
    vector<int> sizes(n + 1, 1);

    for (int i = 1; i <= n; i++)
        roots[i] = i;

    for (int i = 0; i < m; i++)
        cin >> edges[i].s >> edges[i].e >> edges[i].cost;

    // 연결 그래프가 아닌 경우의 귀찮음을 방지하기 위해 1번 노드와 나머지 노드를 모두 다 가중치가 (사실상) 무한인 간선으로 연결한다
    for (int i = 2; i <= n; i++)
        edges.push_back(Edge{1, i, 2 * MAX});

    sort(edges.begin(), edges.end());
    vector<Edge> mstEdges;
    for (auto edge : edges) {
        if (!hasSameRoots(edge.e, edge.s, roots)) {
            mstEdges.push_back(edge);
            unite(edge.e, edge.s, roots, sizes);
        }
    }

    vector<vector<pair<int, int>>> mstAdjList(n + 1);
    for (auto edge : mstEdges) {
        mstAdjList[edge.s].push_back({edge.e, edge.cost});
        mstAdjList[edge.e].push_back({edge.s, edge.cost});
    }

    vector<Query> queries(q);
    vector<pair<int, int>> ans(q);
    for (int i = 0; i < q; i++) {
        queries[i].idx = i;
        cin >> queries[i].x >> queries[i].y;
    }

    vector<vector<int>> parentSparseTable(18, vector<int>(n + 1));
    vector<vector<int>> maxSparseTable(18, vector<int>(n + 1));
    vector<int> depths(n + 1, -1);
    vector<int> parents(n + 1, 0);
    vector<int> costs(n + 1, 0);
    dfs(mstAdjList, parents, depths, costs, 1, 0);
    makeParentSparseTable(parentSparseTable, parents);
    makeMaxSparseTable(maxSparseTable, parentSparseTable, costs);

    for (auto &elem : queries)
        elem.minCost = getMaxCost(parentSparseTable, maxSparseTable, depths, elem.x, elem.y);

    // mst 및 관련 정보 초기화
    for (int i = 1; i <= n; i++)
        roots[i] = i;
    sizes = vector<int>(n + 1, 1);

    sort(queries.begin(), queries.end(), [](Query &x, Query &y) -> bool { return x.minCost < y.minCost; });
    int edgeIdx = 0;
    for (auto &elem : queries) {
        while (edgeIdx < edges.size() && edges[edgeIdx].cost <= elem.minCost) {
            unite(edges[edgeIdx].s, edges[edgeIdx].e, roots, sizes);
            edgeIdx++;
        }
        elem.reachableCnt = getSize(elem.x, roots, sizes);
    }

    sort(queries.begin(), queries.end());
    for (auto &elem : queries) {
        if (elem.minCost > MAX)
            cout << -1 << '\n';

        else
            cout << elem.minCost << ' ' << elem.reachableCnt << '\n';
    }

    return 0;
}