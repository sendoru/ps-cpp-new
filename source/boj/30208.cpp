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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, s;
    cin >> n >> s;
    vector<int> w(n + 1), t(n + 1), p(n + 1, -1);
    int w_sum = 0;
    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w_sum += w[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    // it's more convenient to make virtual root 0
    // as the given graph is a forest
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        adj[p[i]].push_back(i);
    }

    if (accumulate(w.begin(), w.end(), 0) < s) {
        cout << -1;
        return 0;
    }

    // knapsack on tree
    // select node set all of whose parents are also selected (except for the root)
    // with total weight at least s and minimum time t
    function<vector<int>(int)> dfs = [&](int u) {
        vector<int> dp(w_sum + 1, 1e6);
        dp[w[u]] = t[u];
        // combline child dp's
        for (int v : adj[u]) {
            vector<int> child_dp = dfs(v);
            // this node MUST be selected
            // if any one of its children is selected
            for (int i = w_sum - w[u]; i >= 0; i--) {
                for (int j = 0; j <= i + w[u]; j++) {
                    dp[i + w[u]] = min(dp[i + w[u]], dp[i + w[u] - j] + child_dp[j]);
                }
            }
        }
        dp[0] = 0; // this node is not selected
        return dp;
    };

    vector<int> dp = dfs(0);
    int ans = 1e6;
    for (int i = s; i <= w_sum; i++) {
        ans = min(ans, dp[i]);
    }

    cout << ans;

    return 0;
}