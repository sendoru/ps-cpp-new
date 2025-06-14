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

    int n, h, m;
    cin >> n >> h >> m;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(h + 1, -1e9));
    dp[0][h] = m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            // 마법공격
            if (dp[i - 1][j] >= b[i]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] - b[i]);
            }
            // 물리공격
            if (j >= a[i]) {
                dp[i][j - a[i]] = max(dp[i][j - a[i]], dp[i - 1][j]);
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (*max_element(dp[i].begin(), dp[i].end()) >= 0) {
            ans = i;
        }
    }

    cout << ans << "\n";

    return 0;
}