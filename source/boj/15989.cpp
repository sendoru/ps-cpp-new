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

    vector<array<ll, 4>> dp(10001);
    dp[0][1] = 1;
    for (int i = 1; i <= 10000; i++) {
        for (int cur = 1; cur <= 3; cur++) {
            if (i - cur < 0) {
                continue;
            }
            for (int pre = 1; pre <= cur; pre++) {
                dp[i][cur] += dp[i - cur][pre];
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << dp[n][1] + dp[n][2] + dp[n][3] << "\n";
    }

    return 0;
}