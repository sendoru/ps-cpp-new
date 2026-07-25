// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll x, ll m) {
    return modpow(x, m - 2, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;

    if (s[0] == 'x' || s[n - 1] == 'x') {
        cout << 0;
        return 0;
    }

    vector<vector<ll>> dp(n, vector<ll>(n + 1, 0));
    dp[0][1] = 1;
    for (ll i = 1; i < n; i++) {
        ll pf_sum = 0;
        for (ll len = i + 1; len <= n; len++) {
            pf_sum = (pf_sum + dp[i - 1][len - 1]) % MOD9;
            ll cnt_put_inside = dp[i - 1][len] * (len - i) % MOD9;
            ll cnt_extend = 2 * pf_sum % MOD9;
            dp[i][len] = (cnt_put_inside + cnt_extend) % MOD9;
            bool cont = (len == i + 1);
            if (cont != (s[i] == 'o')) {
                dp[i][len] = 0;
            }
        }
    }

    cout << dp[n - 1][n] % MOD9;

    return 0;
}