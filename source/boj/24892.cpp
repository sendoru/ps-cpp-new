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
    b %= m;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
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

    ll n, a, b;
    cin >> n >> a >> b;
    ll len = abs(b - a);
    vector<ll> x(n + 1), y(n + 1);
    ll n_inv = modinv(n, MOD1);
    for (int i = 0; i <= n; i++) {
        x[i] = i * n_inv % MOD1 * len % MOD1;
        y[i] = i * (n - i) % MOD1 * n_inv % MOD1 * n_inv % MOD1 * len % MOD1 * len % MOD1;
    }

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans - x[i] * y[(i + 1) % (n + 1)] % MOD1 + MOD1) % MOD1;
        ans = (ans + x[(i + 1) % (n + 1)] * y[i] % MOD1 + MOD1) % MOD1;
    }

    ans = ans * modinv(2, MOD1) % MOD1;
    cout << ans;

    return 0;
}