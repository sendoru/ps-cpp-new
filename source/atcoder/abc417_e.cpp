// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, s, e;
        cin >> n >> m >> s >> e;
        s--;
        e--;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }

        vector<int> pre(n, -1);
        function<void(int)> dfs = [&](int u) {
            for (auto v : adj[u]) {
                if (pre[v] >= 0) {
                    continue;
                }
                pre[v] = u;
                dfs(v);
            }
        };
        pre[s] = s;
        dfs(s);
        vector<int> path;
        for (int i = e; i != s; i = pre[i]) {
            path.push_back(i);
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        for (auto v : path) {
            cout << v + 1 << " ";
        }
        cout << '\n';
    }

    return 0;
}