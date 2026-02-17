// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll INV_2 = (MOD1 + 1) / 2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<pll> dp(k + 1, {LLONG_MAX, LLONG_MAX});
    dp[0] = {n, n - 1};
    for (int i = 0; i < k; i++) {
        dp[i + 1].first = dp[i].first * dp[i].second % MOD1 * INV_2 % MOD1;
        dp[i + 1].second = 2 * (dp[i].second + MOD1 - 1) % MOD1;
    }

    cout << dp[k].first;

    return 0;
}