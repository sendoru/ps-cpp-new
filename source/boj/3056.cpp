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
    vector<vector<double>> odds(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> odds[i][j];
            odds[i][j] /= 100.0;
        }
    }

    vector<double> dp(1 << n);
    for (int i = 0; i < n; i++) {
        dp[1 << i] = odds[0][i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) != i + 1) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j))) {
                    continue;
                }
                dp[mask | (1 << j)] = max(dp[mask | (1 << j)], dp[mask] * odds[i + 1][j]);
            }
        }
    }

    cout << fixed << setprecision(10) << dp.back() * 100.0;

    return 0;
}