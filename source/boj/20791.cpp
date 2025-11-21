// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll mod) {
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n, x;
        cin >> n >> x;
        if (!cin.good()) {
            break;
        }

        vector<ll> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        ll ans = x;
        for (int i = 0; i < n; i++) {
            ans += (a[i] * b[i]) % MOD1;
            ans %= MOD1;
        }
        ans *= modpow(x, n - 1, MOD1);
        ans %= MOD1;

        cout << ans << '\n';
    }

    return 0;
}