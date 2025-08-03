// #include "atcoder/all"
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
    while (b) {
        if (b & 1) {
            res = res * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

ll fact[(int)4e5 + 5], ifact[(int)4e5 + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i < (int)4e5 + 5; i++) {
        fact[i] = fact[i - 1] * i % MOD9;
    }
    ifact[(int)4e5 + 4] = modinv(fact[(int)4e5 + 4], MOD9);
    for (int i = (int)4e5 + 3; i >= 0; i--) {
        ifact[i] = ifact[i + 1] * (i + 1) % MOD9;
    }

    int t;
    cin >> t;
    while (t--) {
        ll h, w, k;
        cin >> h >> w >> k;
        if (k < h + w - 2) {
            cout << 0 << '\n';
        } else if (k == h + w - 2) {
            ll res = fact[h + w - 2] * ifact[h - 1] % MOD9 * ifact[w - 1] % MOD9;
            cout << res << '\n';
        } else if (k == h + w - 1) {
            ll res = fact[h + w - 2] * ifact[h - 1] % MOD9 * ifact[w - 1] % MOD9;
            res = res * (h * (w - 1) + w * (h - 1) - (h + w - 2)) % MOD9;
            cout << res << '\n';
        } else {
            ll res = fact[h + w - 2] * ifact[h - 1] % MOD9 * ifact[w - 1] % MOD9;
            // ????
            // res = res * (h * (w - 1) + w * (h - 1) - (h + w - 2)) % MOD9;
            // res = res * (h * (w - 1) + w * (h - 1) - (h + w - 2) - 1) % MOD9;
            // res = res * modinv(2, MOD9) % MOD9;
            // ll a = h - 1, b = w - 1;
            // ll minus = 1;
            // minus = minus * a % MOD9 * b % MOD9;
            // minus = minus * modinv(a + b, MOD9) % MOD9;
            // minus = minus * fact[a + b] % MOD9 * ifact[a] % MOD9 * ifact[b] % MOD9;
            // cout << (res - minus + MOD9) % MOD9 << '\n';
        }
    }

    return 0;
}