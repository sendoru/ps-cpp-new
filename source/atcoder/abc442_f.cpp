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
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // not 2d, row-wise
    vector<vector<int>> pf_sum(n, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pf_sum[i][j + 1] = pf_sum[i][j] + (grid[i][j] == '#');
        }
    }

    vector<vector<int>> dp(n, vector<int>(n + 1, 0));
    for (int j = 0; j <= n; j++) {
        int left_black_cnt = pf_sum[0][j];
        int right_white_cnt = (n - j) - (pf_sum[0][n] - pf_sum[0][j]);
        dp[0][j] = left_black_cnt + right_white_cnt;
    }
    for (int i = 1; i < n; i++) {
        vector<int> prev_dp_sf_min(n + 1, dp[i - 1].back());
        for (int j = n - 1; j >= 0; j--) {
            prev_dp_sf_min[j] = min(prev_dp_sf_min[j + 1], dp[i - 1][j]);
        }
        for (int j = 0; j <= n; j++) {
            int left_black_cnt = pf_sum[i][j];
            int right_white_cnt = (n - j) - (pf_sum[i][n] - pf_sum[i][j]);
            dp[i][j] = prev_dp_sf_min[j] + left_black_cnt + right_white_cnt;
        }
    }

    cout << *min_element(dp[n - 1].begin(), dp[n - 1].end());

    return 0;
}