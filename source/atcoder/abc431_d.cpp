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
    vector<ll> w(n), h(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> h[i] >> b[i];
    }

    ll w_sum = accumulate(w.begin(), w.end(), 0LL);

    // dp[i]: (몸통 무게 합) - (머리 무게 합)이 i일 때 최대 가치
    vector<ll> dp(2 * w_sum + 10, -1);
    auto zero_iter = dp.begin() + w_sum;
    *(zero_iter - w[0]) = h[0];
    *(zero_iter + w[0]) = b[0];
    ll cur_w_sum = w[0];

    for (int i = 1; i < n; i++) {
        auto ndp = dp;
        for (int j = -w_sum; j <= w_sum; j++) {
            if (dp[w_sum + j] == -1) {
                continue;
            }

            // 머리에 추가
            if (w_sum + j - w[i] >= 0 && w_sum + j - w[i] < ndp.size()) {
                ndp[w_sum + j - w[i]] = max(ndp[w_sum + j - w[i]], dp[w_sum + j] + h[i]);
            }
            // 몸통에 추가
            if (w_sum + j + w[i] >= 0 && w_sum + j + w[i] < ndp.size()) {
                ndp[w_sum + j + w[i]] = max(ndp[w_sum + j + w[i]], dp[w_sum + j] + b[i]);
            }
        }
        dp = ndp;
    }

    ll ans = *max_element(zero_iter, dp.end());
    cout << ans;

    return 0;
}