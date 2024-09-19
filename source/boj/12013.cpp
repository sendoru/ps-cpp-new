// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<vector<int>> dp(n, vector<int>(n, -1));
    function<int(int, int)> solve = [&](int l, int r) {
        if (l == r) {
            return dp[l][r] = v[l];
        }
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        for (int m = l; m < r; m++) {
            int l_val = solve(l, m);
            int r_val = solve(m + 1, r);
            if (l_val == r_val && l_val >= 0) {
                dp[l][r] = max(dp[l][r], l_val + 1);
            }
        }
        if (dp[l][r] == -1) {
            dp[l][r] = -2;
        }
        return dp[l][r];
    };

    int ans = 0;
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            ans = max(ans, solve(l, r));
        }
    }

    cout << ans << '\n';

    return 0;
}