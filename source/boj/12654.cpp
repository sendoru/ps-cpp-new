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

    vector<vector<ll>> combs(42, vector<ll>(42, 0));
    for (int i = 0; i < 42; i++) {
        combs[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            combs[i][j] = combs[i - 1][j - 1] + combs[i - 1][j];
        }
    }
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int c, n;
        cin >> c >> n;
        vector<ld> dp(c + 1, 0);
        for (int i = c - 1; i >= n; i--) {
            ld remain_prob = (ld)combs[i][n] / combs[c][n];
            for (int j = i + 1; j <= min(c, i + n); j++) {
                ld move_prob = (ld)combs[i][n - (j - i)] * combs[c - i][j - i] / combs[c][n];
                dp[i] += (dp[j] * move_prob) / (1 - remain_prob);
            }
            dp[i] += 1 / (1 - remain_prob);
        }

        cout << "Case #" << t << ": " << fixed << setprecision(9) << dp[n] + 1 << '\n';
    }

    return 0;
}