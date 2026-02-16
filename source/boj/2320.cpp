// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(const vector<string> &s) {
    int n = s.size();
    vector<vector<ll>> dp((1 << n), vector<ll>(n, -1e18));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = s[i].size();
    }
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int last = 0; last < n; last++) {
            if ((mask & (1 << last)) == 0) {
                continue;
            }
            for (int nxt = 0; nxt < n; nxt++) {
                if ((mask & (1 << nxt)) != 0) {
                    continue;
                }
                if (s[last].back() == s[nxt][0]) {
                    dp[mask | (1 << nxt)][nxt] = max(dp[mask | (1 << nxt)][nxt], dp[mask][last] + (ll)s[nxt].size());
                }
            }
        }
    }

    ll ans = 0;
    for (auto &v : dp) {
        ans = max(ans, *max_element(v.begin(), v.end()));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    cout << solve(s);

    return 0;
}