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

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    int p_sum = accumulate(p.begin(), p.end(), 0);
    if (p_sum % 2 != 0) {
        cout << 0;
        return 0;
    }

    // divied into a, b, c, d
    // where sum(a) == sum(b) and sum(c) == sum(d)

    // consider a problem with only a, b
    // sum(a) == sum(b) == p_sum / 2
    // dp[i][j] := using first i elements, number of ways to make sum j
    vector<ll> dp(p_sum / 2 + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = p_sum / 2; j >= p[i]; j--) {
            dp[j] += dp[j - p[i]];
            dp[j] %= MOD9;
        }
    }

    ll c = dp[p_sum / 2];
    ll ans = (c * c) - 2 * c;
    ans = (ans % MOD9 + MOD9) % MOD9;
    cout << ans;

    return 0;
}