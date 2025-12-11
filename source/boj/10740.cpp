// #include "atcoder/all"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MOD9 = 998244353;
const int MOD1 = (int)1e9 + 7;

int solve(vector<int> &a, vector<int> &b, vector<int> &c) {
    int n = a.size();
    vector<int> dp(n, 1e9);
    dp[1] = a[0] + b[1];
    vector<int> a_pf_sum(n, 0);
    a_pf_sum[0] = a[0];
    for (int i = 1; i < n; i++) {
        a_pf_sum[i] = a_pf_sum[i - 1] + a[i];
    }
    vector<int> c_sf_sum(n, 0);
    c_sf_sum[n - 1] = c[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        c_sf_sum[i] = c_sf_sum[i + 1] + c[i];
    }
    for (int i = 2; i < n; i++) {
        dp[i] = min(dp[i - 1] + b[i], a_pf_sum[i - 1] + b[i]);
    }
    int res = 1e9;
    for (int i = 1; i < n - 1; i++) {
        res = min(res, dp[i] + c_sf_sum[i + 1]);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> diff(3, vector<int>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> diff[i][j];
        }
    }

    vector<vector<int>> perm = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 0, 2},
        {1, 2, 0},
        {2, 0, 1},
        {2, 1, 0},
    };

    int ans = 1e9;
    for (auto &p : perm) {
        vector<int> &a = diff[p[0]];
        vector<int> &b = diff[p[1]];
        vector<int> &c = diff[p[2]];
        ans = min(ans, solve(a, b, c));
    }

    cout << ans << "\n";

    return 0;
}