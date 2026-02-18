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

    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> dp(n, -1e18);
    function<void(int)> dfs = [&](int v) {
        dp[v] = a[v];
        for (int u : adj[v]) {
            dfs(u);
            if (dp[u] > 0) {
                dp[v] += dp[u];
            }
        }
    };

    dfs(0);
    cout << dp[0] << "\n";

    return 0;
}