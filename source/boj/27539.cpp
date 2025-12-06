// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct LCA {
    vector<vector<int>> parents;
    vector<int> depth;
    LCA(const vector<vector<int>> &adj_list, int root = 0) {
        int n = (int)adj_list.size();
        int log2n = 0;
        while ((1 << log2n) < n) {
            log2n++;
        }
        parents.assign(log2n, vector<int>(n, -1));
        depth.assign(n, -1);
        depth[root] = 0;
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int nxt : adj_list[cur]) {
                if (depth[nxt] == -1) {
                    depth[nxt] = depth[cur] + 1;
                    parents[0][nxt] = cur;
                    q.push(nxt);
                }
            }
        }
        for (int k = 0; k + 1 < log2n; k++) {
            for (int v = 0; v < n; v++) {
                if (parents[k][v] < 0) {
                    parents[k + 1][v] = -1;
                }
                else {
                    parents[k + 1][v] = parents[k][parents[k][v]];
                }
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int log2n = (int)parents.size();
        for (int k = 0; k < log2n; k++) {
            if (((depth[u] - depth[v]) >> k) & 1) {
                u = parents[k][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int k = log2n - 1; k >= 0; k--) {
            if (parents[k][u] != parents[k][v]) {
                u = parents[k][u];
                v = parents[k][v];
            }
        }
        return parents[0][u];
    }
    int dist(int u, int v) {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};

struct DSU {
    LCA dsu_lca;
    vector<int> parent;
    vector<int> max_elem;
    vector<int> dp;
    DSU (const vector<vector<int>> &adj_list)
        : dsu_lca(adj_list) {
        int n = (int)adj_list.size();
        parent.resize(n);
        max_elem.resize(n);
        dp.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            max_elem[i] = i;
        }
    }
    int find(int u) {
        if (parent[u] == u) {
            return u;
        }
        return parent[u] = find(parent[u]);
    }
    bool same(int u, int v) {
       return find(u) == find(v);
    }
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return;
        }
        // make sure max_elem[u] > max_elem[v]
        if (max_elem[u] < max_elem[v]) {
            swap(u, v);
        }
        int dist = dsu_lca.dist(max_elem[u], max_elem[v]);
        dp[u] = max(dp[u], dp[v] + dist);
        parent[v] = u;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    vector<vector<int>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u = p[u - 1];
        v = p[v - 1];
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    vector<pii> edges;
    for (int i = n - 1; i >= 0; i--) {
        for (int nxt : adj_list[i]) {
            if (i > nxt) {
                edges.push_back({i, nxt});
            }
        }
    }
    reverse(edges.begin(), edges.end());
    DSU dsu(adj_list);
    for (auto [u, v] : edges) {
        dsu.unite(u, v);
    }

    cout << dsu.dp[dsu.find(n - 1)] << "\n";

    return 0;
}