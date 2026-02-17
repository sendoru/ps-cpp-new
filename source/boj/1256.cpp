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

    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            if (dp[i][j] > k) {
                dp[i][j] = k + 1;
            }
        }
    }
    if (dp[n][m] < k) {
        cout << -1 << '\n';
    } else {
        int x = n, y = m;
        string ans;
        while (x > 0 && y > 0) {
            if (dp[x - 1][y] >= k) {
                ans += 'a';
                x--;
            } else {
                ans += 'z';
                k -= dp[x - 1][y];
                y--;
            }
        }
        while (x > 0) {
            ans += 'a';
            x--;
        }
        while (y > 0) {
            ans += 'z';
            y--;
        }
        cout << ans << '\n';
    }

    return 0;
}