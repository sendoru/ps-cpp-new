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

    int c, n;
    cin >> c >> n;
    vector<pii> adj(n);
    for (int i = 0; i < n; i++) {
        cin >> adj[i].first >> adj[i].second;
    }
    vector<int> dp(2222, 1e9);
    dp[0] = 0;
    for (int i = 0; i < dp.size(); i++) {
        for (auto [cost, people] : adj) {
            int ni = min((int)dp.size() - 1, i + people);
            dp[ni] = min(dp[ni], dp[i] + cost);
        }
    }

    int ans = *min_element(dp.begin() + c, dp.end());
    cout << ans << "\n";

    return 0;
}