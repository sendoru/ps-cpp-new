// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m)
{
    ll ret = 1;
    while (e > 0) {
        if (e & 1) {
            ret = (ret * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return ret;
}

ll comb[12][12];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    comb[0][0] = 1;
    for (int i = 1; i < 12; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD9;
        }
    }

    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<ll>> dp(n, vector<ll>(k + 1, -1));
    function<ll(ll, ll)> solve = [&](ll r, ll k) {
        if (r == 0) {
            return modpow(a[0], k, MOD9);
        }
        ll &ret = dp[r][k];
        if (ret != -1) {
            return ret;
        }
        if (k == 1) {
            return ret = (solve(r - 1, k) + (r + 1) * a[r]) % MOD9;
        }
        ret = solve(r - 1, k);
        for (int i = 1; i <= k; i++) {
            ret = ret + solve(r - 1, k - i) * comb[k][i] % MOD9 * modpow(a[r], i, MOD9);
            ret %= MOD9;
        }
        ret += modpow(a[r], k, MOD9);
        ret %= MOD9;
        return ret;
    };

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + solve(i, k)) % MOD9;
    }
    cout << ans << "\n";

    return 0;
}