#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
            if (v[i][j] < 100) {
                v[i][j] = 0;
            }
            else if (v[i][j] == 100) {
                v[i][j] = 1;
            }
            else {
                v[i][j] = 2;
            }
        }
    }

    ll ans = 0;
    vector<vector<ll>> dp(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        dp[0][i] = v[0][i] == 0 ? 0 : 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i][j] == 0) {
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = dp[i - 1][j] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans += dp[i][j];
            if (dp[i][j] >= 1) {
                ll cur = dp[i][j];
                for (int k = j - 1; k >= 0; k--) {
                    cur = min(dp[i][k], cur);
                    if (cur < 1) {
                        break;
                    }
                    ans += cur;
                }
            }
        }
    }

    // -------------------------------

    dp = vector<vector<ll>>(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        dp[0][i] = v[0][i] < 2 ? 0 : 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i][j] < 2) {
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = dp[i - 1][j] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans -= dp[i][j];
            if (dp[i][j] >= 1) {
                ll cur = dp[i][j];
                for (int k = j - 1; k >= 0; k--) {
                    cur = min(dp[i][k], cur);
                    if (cur < 1) {
                        break;
                    }
                    ans -= cur;
                }
            }
        }
    }

    cout << ans;

    return 0;
}