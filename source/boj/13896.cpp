// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_parents(vector<vector<int>> &adj_list, int root) {
    vector<int> parents(adj_list.size(), -1);
    function<void(int, int)> dfs = [&](int cur, int pre) -> void {
        parents[cur] = pre;
        for (auto &nxt : adj_list[cur]) {
            if (parents[nxt] == -1) {
                dfs(nxt, cur);
            }
        }
    };

    dfs(root, root);
    parents[root] = -1;
    return parents;
}

vector<int> get_depths(vector<vector<int>> &adj_list, int root) {
    vector<int> depths(adj_list.size(), -1);
    function<void(int, int)> dfs = [&](int cur, int cur_depth) -> void {
        depths[cur] = cur_depth;
        for (auto &nxt : adj_list[cur]) {
            if (depths[nxt] == -1) {
                dfs(nxt, cur_depth + 1);
            }
        }
    };

    dfs(root, root);
    return depths;
}

vector<int> get_subtree_sizes(vector<vector<int>> &adj_list, int root) {
    vector<int> subtree_sizes(adj_list.size());
    function<void(int, int)> dfs = [&](int cur, int pre) -> void {
        subtree_sizes[cur] = 1;
        for (auto &nxt : adj_list[cur]) {
            if (nxt != pre) {
                dfs(nxt, cur);
                subtree_sizes[cur] += subtree_sizes[nxt];
            }
        }
    };

    dfs(root, root);
    return subtree_sizes;
}

vector<vector<int>> make_sparse_table(vector<int> &parents) {
    int n = parents.size();
    int log2 = 1;
    while ((1 << log2) < n) {
        log2++;
    }
    log2++;
    vector<vector<int>> sparse_table(log2, vector<int>(n));
    for (int i = 0; i < n; i++) {
        sparse_table[0][i] = parents[i];
    }
    for (int i = 1; i < log2; i++) {
        for (int j = 0; j < n; j++) {
            if (sparse_table[i - 1][j] == -1) {
                sparse_table[i][j] = -1;
            } else {
                sparse_table[i][j] = sparse_table[i - 1][sparse_table[i - 1][j]];
            }
        }
    }

    return sparse_table;
}

int get_lca(vector<vector<int>> &sparse_table, vector<int> &depth, int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    int log2 = sparse_table.size();
    for (int i = log2 - 1; i >= 0; i--) {
        if (depth[u] - depth[v] >= (1 << i)) {
            u = sparse_table[i][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = log2 - 1; i >= 0; i--) {
        if (sparse_table[i][u] != sparse_table[i][v]) {
            u = sparse_table[i][u];
            v = sparse_table[i][v];
        }
    }
    return sparse_table[0][u];
}

int f(vector<vector<int>> &sparse_table, vector<int> &depth, int r, int u) {
    int log2 = sparse_table.size();
    for (int i = log2 - 1; i >= 0; i--) {
        if (depth[r] - depth[u] > (1 << i)) {
            r = sparse_table[i][r];
        }
    }

    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n, q, r;
        cin >> n >> q >> r;
        vector<vector<int>> adj_list(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int s, e;
            cin >> s >> e;
            adj_list[s].push_back(e);
            adj_list[e].push_back(s);
        }

        auto parents = get_parents(adj_list, 1);
        auto depths = get_depths(adj_list, 1);
        auto subtree_sizes = get_subtree_sizes(adj_list, 1);
        auto sparse_table = make_sparse_table(parents);
        cout << "Case #" << t << ":\n";
        while (q--) {
            int s, u;
            cin >> s >> u;
            if (s == 0) {
                r = u;
            } else {
                if (u == r) {
                    cout << n << '\n';
                    continue;
                }
                int lca = get_lca(sparse_table, depths, r, u);
                if (lca == u) {
                    int r_asc = f(sparse_table, depths, r, u);
                    cout << n - subtree_sizes[r_asc] << '\n';
                } else {
                    cout << subtree_sizes[u] << '\n';
                }
            }
        }
    }

    return 0;
}