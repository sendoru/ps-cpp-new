// #include "atcoder/all"
#pragma GCC optimize("Ofast")
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
    vector<array<ll, 3>> edges;
    vector<vector<ll>> adj_mat(n, vector<ll>(n));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int w;
            cin >> w;
            if (i < j)
                edges.push_back({w, i - 1, j - 1});
            adj_mat[i - 1][j - 1] = w;
        }
    }

    sort(edges.begin(), edges.end());
    Dsu dsu(n);
    vector<vector<ll>> adj_list(n);
    for (auto [w, u, v] : edges) {
        if (!dsu.same(u, v)) {
            dsu.unite(u, v);
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }
    }

    vector<vector<ll>> adj_mat_recon(n, vector<ll>(n, -1));
    for (int root = 0; root < n; root++) {
        vector<ll> &dist = adj_mat_recon[root];
        dist[root] = 0;
        queue<ll> q;
        q.push(root);
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            for (ll v : adj_list[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + adj_mat[u][v];
                    if (dist[v] != adj_mat[root][v]) {
                        cout << "No";
                        return 0;
                    }
                    q.push(v);
                }
            }
        }
    }

    cout << "Yes";

    return 0;
}