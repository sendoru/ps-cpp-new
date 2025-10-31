// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int get_lca(int u, int v, const vector<int> &level, const vector<vector<int>> &sparse_table) {
    if (level[u] < level[v])
        swap(u, v);
    int diff = level[u] - level[v];
    for (int k = 0; k < (int)sparse_table.size(); k++) {
        if (diff & (1 << k)) {
            u = sparse_table[k][u];
        }
    }
    if (u == v)
        return u;
    for (int k = (int)sparse_table.size() - 1; k >= 0; k--) {
        if (sparse_table[k][u] != sparse_table[k][v]) {
            u = sparse_table[k][u];
            v = sparse_table[k][v];
        }
    }
    return sparse_table[0][u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<array<ll, 4>> edges(n - 1);
    vector<ll> c1(n + 1), c2(n + 1);
    vector<int> parent(n + 1, -1);
    vector<int> level(n + 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2] >> edges[i][3];
        adj[edges[i][0]].push_back(edges[i][1]);
        adj[edges[i][1]].push_back(edges[i][0]);
    }

    parent[1] = 1;
    level[1] = 0;
    function<void(int)> dfs = [&](int u) {
        for (int v : adj[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                level[v] = level[u] + 1;
                dfs(v);
            }
        }
    };
    dfs(1);

    for (auto &[u, v, cost1, cost2] : edges) {
        if (parent[v] == u) {
            c1[v] = cost1;
            c2[v] = cost2;
        } else {
            c1[u] = cost1;
            c2[u] = cost2;
        }
    }

    vector<vector<int>> sparse_table(18, vector<int>(n + 1));
    sparse_table[0] = parent;
    for (int k = 1; k < 18; k++) {
        for (int v = 1; v <= n; v++) {
            sparse_table[k][v] = sparse_table[k - 1][sparse_table[k - 1][v]];
        }
    }

    vector<ll> imos(n + 1);

    for (int i = 1; i < n; i++) {
        int lca = get_lca(i, i + 1, level, sparse_table);
        imos[i] += 1;
        imos[i + 1] += 1;
        imos[lca] -= 2;
    }

    function<void(int)> dfs_imos = [&](int u) {
        for (int v : adj[u]) {
            if (parent[v] == u) {
                dfs_imos(v);
                imos[u] += imos[v];
            }
        }
    };
    dfs_imos(1);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += min(c1[i] * imos[i], c2[i]);
    }

    cout << ans << "\n";

    return 0;
}