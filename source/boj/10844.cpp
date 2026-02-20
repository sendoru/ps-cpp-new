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

    int n;
    cin >> n;
    vector<vector<ll>> dp(n + 1, vector<ll>(10));
    for (int i = 1; i <= 9; i++) {
        dp[1][i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j - 1 >= 0) {
                dp[i][j] += dp[i - 1][j - 1];
            }
            if (j + 1 <= 9) {
                dp[i][j] += dp[i - 1][j + 1];
            }
            dp[i][j] %= MOD;
        }
    }
    cout << accumulate(dp[n].begin(), dp[n].end(), 0LL) % MOD << "\n";

    return 0;
}