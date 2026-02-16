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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        int par;
        cin >> par;
        par--;
        if (par >= 0) {
            adj[par].push_back(i);
        }
    }

    vector<int> val(n);
    for (int i = 0; i < m; i++) {
        int idx, v;
        cin >> idx >> v;
        idx--;
        val[idx] += v;
    }

    vector<int> dp(n);
    function<void(int, int)> dfs = [&](int v, int s) {
        dp[v] = s + val[v];
        for (int nv : adj[v]) {
            dfs(nv, s + val[v]);
        }
    };

    dfs(0, 0);

    for (int i = 0; i < n; i++) {
        cout << dp[i] << ' ';
    }

    return 0;
}