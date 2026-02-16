// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MOD = 1'000'000'000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    vector<ll> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < k; i++) {
        vector<ll> ndp(n + 1);
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= j; k++) {
                ndp[j] = (ndp[j] + dp[k]) % MOD;
            }
        }
        dp = ndp;
    }
    cout << dp[n];

    return 0;
}