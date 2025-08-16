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

    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    vector<vector<int>> incs(l, vector<int>(m, 0));

    for (int i = 0; i < l; i++) {
        for (int mod = 0; mod < m; mod++) {
            int inc = 0;
            for (int j = i; j < n; j += l) {
                int target = a[j] / m * m + mod;
                if (target < a[j]) {
                    target += m;
                }
                inc += target - a[j];
            }
            incs[i][mod] = inc;
        }
    }

    vector<vector<ll>> dp(l, vector<ll>(m, INT_MAX));
    for (int i = 0; i < m; i++) {
        dp[0][i] = incs[0][i];
    }

    for (int i = 1; i < l; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + incs[i][(j - k + m) % m]);
            }
        }
    }

    cout << dp[l - 1][0] << '\n';

    return 0;
}