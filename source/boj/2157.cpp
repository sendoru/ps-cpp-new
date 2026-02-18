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

    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<array<ll, 2>>> nxt(n);
    for (int i = 0; i < k; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        if (u > v) {
            continue;
        }
        u--;
        v--;
        nxt[u].push_back({v, w});
    }

    vector<vector<ll>> dp(n, vector<ll>(m + 1, -1e18));
    dp[0][1] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (dp[i][j] < 0) {
                continue;
            }
            for (auto [ni, w] : nxt[i]) {
                dp[ni][j + 1] = max(dp[ni][j + 1], dp[i][j] + w);
            }
        }
    }

    cout << *max_element(dp[n - 1].begin(), dp[n - 1].end()) << "\n";

    return 0;
}