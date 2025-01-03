// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> fac(600);
vector<ll> fac_inv(600);

ll mod_pow(ll a, ll b, ll mod) {
    ll ret = 1;
    while (b) {
        if (b & 1) {
            ret = ret * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

ll mod_inv(ll a, ll mod) {
    return mod_pow(a, mod - 2, mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fac[0] = 1;
    for (int i = 1; i < 600; i++) {
        fac[i] = fac[i - 1] * i % MOD1;
    }
    fac_inv[599] = mod_inv(fac[599], MOD1);
    for (int i = 598; i >= 0; i--) {
        fac_inv[i] = fac_inv[i + 1] * (i + 1) % MOD1;
    }

    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        ll ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans = ans * (a[j] - a[i]) % MOD1;
            }
        }
        for (int i = 0; i < n; i++) {
            ans = ans * fac_inv[i] % MOD1;
        }

        cout << ans << '\n';
    }

    return 0;
}