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
        int v, e;
        cin >> v >> e;
        vector<vector<int>> adj(v);
        for (int i = 0; i < e; i++) {
            int v1, v2;
            cin >> v1 >> v2;
            v1--;
            v2--;
            adj[v1].push_back(v2);
            adj[v2].push_back(v1);
        }

        vector<int> color(v, -1);
        bool is_bipartite = true;
        function<void(int, int)> dfs = [&](int node, int c) {
            color[node] = c;
            for (int next : adj[node]) {
                if (color[next] == -1) {
                    dfs(next, 1 - c);
                } else if (color[next] == c) {
                    is_bipartite = false;
                    return;
                }
            }
        };

        for (int i = 0; i < v; i++) {
            if (color[i] == -1) {
                dfs(i, 0);
            }
            if (!is_bipartite) {
                break;
            }
        }
        cout << (is_bipartite ? "YES" : "NO") << "\n";
    }

    return 0;
}