// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MAX = 222'222;
vector<ll> fact(MAX + 1), inv_fact(MAX + 1), pow_2(MAX + 1);

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    b %= m;
    while (e > 0) {
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

ll comb(ll n, ll r) {
    if (r < 0 || r > n) {
        return 0;
    }
    return fact[n] * inv_fact[r] % MOD1 * inv_fact[n - r] % MOD1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fact[0] = 1;
    for (ll i = 1; i <= MAX; i++) {
        fact[i] = fact[i - 1] * i % MOD1;
    }
    inv_fact[MAX] = modinv(fact[MAX], MOD1);
    for (ll i = MAX - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD1;
    }
    pow_2[0] = 1;
    for (ll i = 1; i <= MAX; i++) {
        pow_2[i] = pow_2[i - 1] * 2ll % MOD1;
    }

    ll n;
    cin >> n;
    vector<ll> a(n), b(n);
    vector<ll> a_pf(n + 1), b_pf(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        a_pf[a[i]]++;
        b_pf[b[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        a_pf[i] += a_pf[i - 1];
        b_pf[i] += b_pf[i - 1];
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll exp_2 = b_pf[a[i] - 1] + a_pf.back() - a_pf[a[i] - 1] - 1;
        ll target = a[i] - 1 - b_pf[a[i] - 1];
        ans += pow_2[exp_2] * comb(n - 1 - exp_2, target) % MOD1;
        ans %= MOD1;

        exp_2 = b_pf[b[i] - 1] + a_pf.back() - a_pf[b[i] - 1];
        target = b[i] - 1 - b_pf[b[i] - 1];
        ans += pow_2[exp_2] * comb(n - 1 - exp_2, target) % MOD1;
        ans %= MOD1;
    }

    cout << ans << '\n';

    return 0;
}