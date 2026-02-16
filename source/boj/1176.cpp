// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(const vector<ll> &a, ll k) {
    int n = a.size();
    vector<vector<ll>> dp(1 << n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 1;
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0) {
                continue;
            }
            for (int nxt = 0; nxt < n; nxt++) {
                if ((mask & (1 << nxt)) != 0) {
                    continue;
                }
                if (abs(a[i] - a[nxt]) > k) {
                    dp[mask | (1 << nxt)][nxt] += dp[mask][i];
                }
            }
        }
    }

    return accumulate(dp.back().begin(), dp.back().end(), 0LL);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << solve(a, k) << '\n';

    return 0;
}