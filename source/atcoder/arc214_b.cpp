// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<pii>> adj(n);
        vector<pii> edges;
        for (int i = 0; i < m; i++) {
            int u, v, b;
            cin >> u >> v >> b;
            u--;
            v--;
            adj[u].emplace_back(v, b);
            adj[v].emplace_back(u, b);
            edges.emplace_back(u, v);
        }
        if (n % 2) {
            cout << -1 << '\n';
            continue;
        }

        // 1) make random spanning tree
        vector<int> parent(n, -1);
        parent[0] = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, b] : adj[u]) {
                if (parent[v] == -1) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        vector<vector<pii>> tree(n);
        for (int v = 1; v < n; v++) {
            int u = parent[v];
            for (auto [w, b] : adj[v]) {
                if (w == u) {
                    tree[u].emplace_back(v, b);
                    tree[v].emplace_back(u, b);
                    break;
                }
            }
        }

        // 2) select edges so that all degress are odd
        vector<int> deg(n, -1);
        int edge_xor = 0;
        function<void(int)> dfs = [&](int u) {
            deg[u] = 0;
            for (auto [v, b] : tree[u]) {
                if (deg[v] == -1) {
                    dfs(v);
                    if (deg[v] % 2 == 0) {
                        deg[u]++;
                        edge_xor ^= b;
                    }
                }
            }
        };
        dfs(0);

        int all_xor = 0;
        for (int i = 1; i <= n; i++) {
            all_xor ^= i;
        }
        cout << (edge_xor ^ all_xor) << '\n';
    }

    return 0;
}