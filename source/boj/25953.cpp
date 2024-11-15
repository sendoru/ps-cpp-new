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

    ll n, t, m;
    cin >> n >> t >> m;
    vector<ll> dp(n, 1e16);
    int s, e;
    cin >> s >> e;
    dp[s] = 0;
    for (int i = 0; i < t; i++) {
        vector<ll> new_dp = dp;
        for (int j = 0; j < m; j++) {
            ll s, e, w;
            cin >> s >> e >> w;
            new_dp[e] = min(new_dp[e], dp[s] + w);
            new_dp[s] = min(new_dp[s], dp[e] + w);
        }
        dp = new_dp;
    }

    cout << (dp[e] >= 1e16 ? -1 : dp[e]) << endl;

    return 0;
}