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

    int t;
    cin >> t;
    while (t--) {
        int n, l;
        cin >> n >> l;
        vector<vector<__int128_t>> dp(l, vector<__int128_t>(n + 1, 0));
        for (int i = 1; i <= n; i++) {
            dp[0][i] = 1;
        }
        for (ll i = 1; i < l; i++) {
            for (ll j = 1; j <= n; j++) {
                __int128_t bound = j * j + 1;
                if (bound > n) {
                    continue;
                }
                dp[i][j] += dp[i - 1][bound];
            }
            for (int j = n - 1; j >= 1; j--) {
                dp[i][j] += dp[i][j + 1];
            }
        }
        if (n == 1) {
            cout << (ll)dp[l - 1][1] << "\n";
        } else {
            cout << (ll)(dp[l - 1][1] - dp[l - 1][2]) << "\n";
        }
    }

    return 0;
}