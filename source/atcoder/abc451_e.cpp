// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    int n;
    vector<int> parent;

    Dsu(int n) : n(n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            parent[y] = x;
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<array<int, 3>> edges;
    vector<vector<int>> adj_mat(n, vector<int>(n));
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int w;
            cin >> w;
            edges.push_back({w, i - 1, j - 1});
            adj_mat[i - 1][j - 1] = w;
            adj_mat[j - 1][i - 1] = w;
        }
    }

    sort(edges.begin(), edges.end());
    Dsu dsu(n);
    vector<vector<int>> adj_list(n);
    for (auto [w, u, v] : edges) {
        if (!dsu.same(u, v)) {
            dsu.unite(u, v);
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }
    }

    vector<vector<int>> adj_mat_recon(n, vector<int>(n, -1));
    for (int root = 0; root < n; root++) {
        vector<int> &dist = adj_mat_recon[root];
        dist[root] = 0;
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj_list[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + adj_mat[u][v];
                    q.push(v);
                }
            }
        }
    }

    if (adj_mat == adj_mat_recon) {
        cout << "Yes";
    } else {
        cout << "No";
    }

    return 0;
}