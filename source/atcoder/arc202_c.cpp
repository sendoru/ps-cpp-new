// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
ll MODINV_9;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = (res * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

ll get_r(ll a) {
    ll res = modpow(10, a, MOD9) - 1 + MOD9;
    return (res * MODINV_9) % MOD9;
}

ll gcd_r(ll a, ll b) {
    ll gcd_ab = __gcd(a, b);
    ll res = modpow(10, gcd_ab, MOD9) - 1 + MOD9;
    return (res * MODINV_9) % MOD9;
}

map<ll, ll> factorize(ll n) {
    map<ll, ll> factors;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    if (n > 1) {
        factors[n]++;
    }
    return factors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    MODINV_9 = modinv(9, MOD9);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> prods(n);
    prods[0] = get_r(a[0]);
    for (int i = 1; i < n; i++) {
        prods[i] = prods[i - 1] * get_r(a[i]) % MOD9;
    }
    vector<ll> ans = prods;
    map<ll, ll> factors;
    ll div = 1;
    for (int i = 0; i < n; i++) {
        auto cur_factors = factorize(a[i]);
        map<ll, ll> cofactors;
        for (const auto &[p, exp] : cur_factors) {
            cofactors[p] = min(factors[p], exp);
        }
        // do something
        ll pow = 1;
        for (const auto &[p, exp] : cofactors) {
            // fermat's little theorem
            pow *= modpow(p, exp, MOD9 - 1);
            pow %= MOD9 - 1;
        }
        div *= get_r(pow);
        div %= MOD9;
        ans[i] = prods[i] * modinv(div, MOD9) % MOD9;
        for (const auto &[p, exp] : cur_factors) {
            factors[p] = max(factors[p], exp);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}

// 429620650 844699313 355160870 608402385 858856681 605347397 566966598 91535363 4945124 59297328