// #include "atcoder/all"
#pragma GCC optimize("Ofast")
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

    int n, k;
    cin >> n >> k;
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, -1));

    function<ll(int, int)> get_dp = [&](int len, int height) -> ll {
        if (height < 0) {
            return 0;
        }
        if (height == 0) {
            return len == 0;
        }
        if (len <= 1) {
            return 1;
        }
        if (dp[len][height] != -1) {
            return dp[len][height];
        }
        ll &ret = dp[len][height] = 0;
        for (int mid = 0; mid < len; mid++) {
            int left = mid, right = len - mid - 1;
            ret += get_dp(left, height - 1) * get_dp(right, height - 1);
            ret %= MOD1;
        }
        return ret;
    };

    dp[0][0] = 1;
    for (int i = 1; i <= k; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= k; j++) {
        }
    }

    cout << get_dp(n, k) << '\n';
    return 0;
}