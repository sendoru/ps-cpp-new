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
        assert(m == n - 1);
        vector<vector<pll>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--;
            v--;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        if (n == 1) {
            cout << "0\n";
            continue;
        }

        vector<vector<int>> adj_dir(n);
        vector<ll> weights(n, 0);

        function<void(int, int)> dfs = [&](int v, int p) {
            for (auto &[nv, w] : adj[v]) {
                if (nv == p) {
                    continue;
                }
                weights[nv] = w;
                adj_dir[v].push_back(nv);
                dfs(nv, v);
            }
        };
        dfs(0, -1);
        weights[0] = 1e15;

        vector<ll> dp(n, -1);
        function<ll(int)> dfs2 = [&](int v) {
            if (dp[v] != -1) {
                return dp[v];
            }
            if (adj_dir[v].empty()) {
                return dp[v] = weights[v];
            }
            ll child_sum = 0;
            for (int nv : adj_dir[v]) {
                child_sum += dfs2(nv);
            }
            return dp[v] = min(weights[v], child_sum);
        };

        cout << dfs2(0) << '\n';
    }

    return 0;
}