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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(3, 1e6)));
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < 3; k++) {
            dp[0][j][k] = grid[0][j];
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 3; k++) {
                for (int d = -1; d <= 1; d++) {
                    int nj = j + d;
                    if (nj >= 0 && nj < m && d + 1 != k) {
                        dp[i + 1][nj][d + 1] = min(dp[i + 1][nj][d + 1], dp[i][j][k] + grid[i + 1][nj]);
                    }
                }
            }
        }
    }

    int ans = INT32_MAX;
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < 3; k++) {
            ans = min(ans, dp[n - 1][j][k]);
        }
    }

    cout << ans;

    return 0;
}