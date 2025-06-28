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

    ll k, l;
    cin >> k >> l;
    vector<vector<ll>> mat(k, vector<ll>(k));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            cin >> mat[i][j];
        }
    }

    int n;
    cin >> n;
    vector<ll> p(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
    }

    vector<vector<ll>> dp(n, vector<ll>(k, 0));
    for (int i = 0; i < k; i++) {
        dp[0][i] = 1;
    }

    for (int i = 0; i < n - 1; i++) {
        vector<ll> imos(k + 1, 0);
        for (int j = 0; j < k; j++) {
            int lb = lower_bound(mat[j].begin(), mat[j].end(), p[i + 1] - l) - mat[j].begin();
            int ub = upper_bound(mat[j].begin(), mat[j].end(), p[i + 1] + l) - mat[j].begin();
            imos[lb] += dp[i][j];
            imos[ub] -= dp[i][j];
        }
        for (int j = 0; j < k; j++) {
            imos[j + 1] += imos[j];
        }
        for (int j = 0; j < k; j++) {
            dp[i + 1][j] = imos[j] % MOD1;
        }
    }

    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans += dp[n - 1][i];
        ans %= MOD1;
    }
    cout << ans << '\n';

    return 0;
}