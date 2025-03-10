// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

class WeightedTreeWithSparseTable {
    vector<int> depth;
    vector<vector<int>> parent_sparse_table;
    vector<vector<ll>> weight_sparse_table;
    vector<vector<int>> adj_list;
    vector<vector<ll>> weight_list;
    int n, log_n;

  public:
    WeightedTreeWithSparseTable(vector<vector<int>> &adj_list, vector<vector<ll>> &weight_list) {
        n = adj_list.size();
        log_n = 32 - __builtin_clz(n);
        depth.resize(n);
        parent_sparse_table.resize(n, vector<int>(log_n));
        weight_sparse_table.resize(n, vector<ll>(log_n));
        this->adj_list = adj_list;
        this->weight_list = weight_list;
        dfs(0, -1, 0, 0);
        for (int j = 1; j < log_n; j++) {
            for (int i = 0; i < n; i++) {
                if (parent_sparse_table[i][j - 1] == -1) {
                    parent_sparse_table[i][j] = -1;
                    weight_sparse_table[i][j] = 0;
                } else {
                    parent_sparse_table[i][j] = parent_sparse_table[parent_sparse_table[i][j - 1]][j - 1];
                    weight_sparse_table[i][j] = weight_sparse_table[i][j - 1] + weight_sparse_table[parent_sparse_table[i][j - 1]][j - 1];
                }
            }
        }
    }

    void dfs(int node, int parent, int d, ll w) {
        depth[node] = d;
        parent_sparse_table[node][0] = parent;
        weight_sparse_table[node][0] = w;
        for (int i = 0; i < adj_list[node].size(); i++) {
            int next = adj_list[node][i];
            ll weight = weight_list[node][i];
            if (next == parent) {
                continue;
            }
            dfs(next, node, d + 1, weight);
        }
    }

    int get_lca(int a, int b) {
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        for (int i = log_n - 1; i >= 0; i--) {
            if (depth[b] - depth[a] >= (1 << i)) {
                b = parent_sparse_table[b][i];
            }
        }
        if (a == b) {
            return a;
        }
        for (int i = log_n - 1; i >= 0; i--) {
            if (parent_sparse_table[a][i] != parent_sparse_table[b][i]) {
                a = parent_sparse_table[a][i];
                b = parent_sparse_table[b][i];
            }
        }
        return parent_sparse_table[a][0];
    }

    ll get_dist(int a, int b) {
        int lca = get_lca(a, b);
        ll dist = 0;
        int da = depth[a] - depth[lca], db = depth[b] - depth[lca];
        for (int i = log_n - 1; i >= 0; i--) {
            if (da >= (1 << i)) {
                dist += weight_sparse_table[a][i];
                a = parent_sparse_table[a][i];
                da -= (1 << i);
            }
            if (db >= (1 << i)) {
                dist += weight_sparse_table[b][i];
                b = parent_sparse_table[b][i];
                db -= (1 << i);
            }
        }
        return dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj_list(n);
    vector<vector<ll>> weight_list(n);
    for (int i = 0; i < n - 1; i++) {
        int s, e;
        ll w;
        cin >> s >> e >> w;
        s--;
        e--;
        adj_list[s].push_back(e);
        adj_list[e].push_back(s);
        weight_list[s].push_back(w);
        weight_list[e].push_back(w);
    }

    int q;
    cin >> q;
    WeightedTreeWithSparseTable wt(adj_list, weight_list);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        cout << wt.get_dist(a, b) << '\n';
    }

    return 0;
}