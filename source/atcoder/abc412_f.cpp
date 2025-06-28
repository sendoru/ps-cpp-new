#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, c;
    cin >> n >> c;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        a[i] = ai;
    }

    a[c - 1]++;
    c = a[c - 1];
    sort(a.begin(), a.end(), greater<ll>());

    ll sam1 = 0;
    for (int i = 0; i < n; i++) {
        sam1 += a[i];
    }
    sam1 = (sam1 - 1) % MOD9;

    vector<ll> dp(n, 0);
    vector<ll> dp2(n, 0);
    vector<ll> dp3(n, 0);

    for (int i = n - 2; i >= 0; i--) {
        dp2[i] = dp2[i + 1] + (a[i + 1]) * modinv(sam1, MOD9) % MOD9;
        dp2[i] %= MOD9;
    }

    dp[0] = modinv(MOD9 + 1 - dp2[0], MOD9) % MOD9;
    dp3[0] = dp[0] * (a[0] * modinv(sam1, MOD9) % MOD9) % MOD9;
    if (a[0] == c) {
        cout << dp[0] << endl;
        return 0;
    }

    for (int i = 1; i < n; i++) {
        dp[i] = (1 + dp3[i - 1]) * modinv(MOD9 + 1 - dp2[i], MOD9) % MOD9;
        dp3[i] = dp[i] * (a[i] * modinv(sam1, MOD9) % MOD9) % MOD9;
        dp3[i] = (dp3[i] + dp3[i - 1]) % MOD9;
        if (a[i] == c) {
            cout << dp[i] << endl;
            return 0;
        }
    }

    return 0;
}