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

    int n, r, q;
    cin >> n >> r >> q;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> sz(n + 1, -1);
    function<int(int)> dfs = [&](int u) {
        if (sz[u] != -1)
            return sz[u];
        sz[u] = 1;
        for (int v : adj[u]) {
            if (sz[v] == -1) {
                sz[u] += dfs(v);
            }
        }
        return sz[u];
    };

    dfs(r);

    while (q--) {
        int u;
        cin >> u;
        cout << sz[u] << '\n';
    }

    return 0;
}