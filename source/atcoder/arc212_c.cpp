// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll MAX = 2e7 + 10;
vector<ll> fact(MAX), invfact(MAX);

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1)
            res = res * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

ll comb(ll n, ll r) {
    if (r < 0 || r > n)
        return 0;
    return fact[n] * invfact[r] % MOD9 * invfact[n - r] % MOD9;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fact[0] = 1;
    for (ll i = 1; i < MAX; i++) {
        fact[i] = fact[i - 1] * i % MOD9;
    }
    invfact[MAX - 1] = modinv(fact[MAX - 1], MOD9);
    for (ll i = MAX - 2; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1) % MOD9;
    }

    ll n, m;
    cin >> n >> m;
    if (n < m) {
        cout << 0;
        return 0;
    }

    ll k = n - m;
    ll ans = 0;
    for (ll i = 0; i <= k / 2; i++) {
        ll t1 = comb(m + i - 1, i);
        ll t2 = comb(2 * m + k - 2 * i - 1, k - 2 * i);
        ans += t1 * t2 % MOD9;
        ans %= MOD9;
    }
    ans = ans * modpow(2, m, MOD9) % MOD9;
    cout << ans;

    return 0;
}