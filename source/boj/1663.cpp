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

    int type;
    cin >> type;
    int n;
    cin >> n;
    vector<array<ll, 3>> dp(n + 1, {0, 0, 0});
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i - 1][2];
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][0] + dp[i - 1][1];
    }
    if (type == 1) {
        cout << accumulate(dp[n].begin(), dp[n].end(), 0LL);
    } else if (type == 2) {
        ll k;
        cin >> k;
        k--;
        // n단계 string = (n - 3)단계 string + (n - 2)단계 string
        vector<string> ss = {"", "X", "YZ", "ZX", "XYZ"};
        while (n > 4) {
            ll pre_len = accumulate(dp[n - 3].begin(), dp[n - 3].end(), 0LL);
            // ll suf_len = accumulate(dp[n - 2].begin(), dp[n - 2].end(), 0LL);
            if (k < pre_len) {
                n -= 3;
            } else {
                k -= pre_len;
                n -= 2;
            }
        }
        cout << ss[n][k];
    } else {
        char ch;
        cin >> ch;
        cout << dp[n][ch - 'X'];
    }

    return 0;
}

// XYZYZZX