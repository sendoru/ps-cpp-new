// #include "atcoder/all"
#pragma GCC optimize("O3,Ofast,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int bit_rev(int x, int log2) {
    int ret = 0;
    for (int i = 0; i < log2; i++) {
        ret <<= 1;
        ret |= (x & 1);
        x >>= 1;
    }
    return ret;
}

ll modpow(ll b, ll e, ll m) {
    ll ret = 1;
    b %= m;
    while (e > 0) {
        if (e & 1) {
            ret = (ret * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return ret;
}

void ntt(vector<ll> &v, ll mod, ll proot, bool inv = false) {
    int n = v.size();
    int log2 = 0;
    while ((1 << log2) < n) {
        log2++;
    }
    for (int i = 0; i < n; i++) {
        int i_rev = bit_rev(i, log2);
        if (i < i_rev) {
            swap(v[i], v[i_rev]);
        }
    }

    vector<ll> roots(n);
    ll x = modpow(proot, (mod - 1) / n, mod);
    if (inv) {
        x = modpow(x, mod - 2, mod);
    }
    roots[0] = 1;
    for (int i = 1; i < n; i++) {
        roots[i] = (roots[i - 1] * x) % mod;
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll ang = roots[n / len];
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = v[i + j];
                ll vj = (v[i + j + len / 2] * w) % mod;
                v[i + j] = (u + vj) % mod;
                v[i + j + len / 2] = (u - vj + mod) % mod;
                w = (w * ang) % mod;
            }
        }
    }
    if (inv) {
        ll n_inv = modpow(n, mod - 2, mod);
        for (int i = 0; i < n; i++) {
            v[i] = (v[i] * n_inv) % mod;
        }
    }
}

vector<ll> convolve(vector<ll> a, vector<ll> b, ll mod, ll root) {
    int n = a.size() + b.size();
    int log2 = 0;
    while ((1 << log2) < n) {
        log2++;
    }
    n = 1 << log2;

    a.resize(n);
    b.resize(n);
    vector<ll> res(n);

    ntt(a, mod, root);
    ntt(b, mod, root);

    for (int i = 0; i < n; i++) {
        res[i] = (a[i] * b[i]) % mod;
    }

    ntt(res, mod, root, true);
    return res;
}

// given m1, r1, m2, r2
// returns x s.t. x % m1 = r1 and x % m2 = r2
// assuming m1 and m2 are coprime
__int128 crt(ll m1, ll r1, ll m2, ll r2) {
    __int128_t m = m1 * m2;
    __int128_t inv_m1 = modpow(m1, m2 - 2, m2);
    __int128_t inv_m2 = modpow(m2, m1 - 2, m1);
    __int128_t x = (r1 * m2 * inv_m2 + r2 * m1 * inv_m1) % m;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    n++;
    m++;
    vector<ll> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    ll m1 = 998244353, m2 = 2281701377;
    ll r1 = 3, r2 = 3;

    vector<ll> res1 = convolve(a, b, m1, r1);
    vector<ll> res2 = convolve(a, b, m2, r2);
    vector<ll> res(res1.size());
    for (int i = 0; i < res.size(); i++) {
        res[i] = crt(m1, res1[i], m2, res2[i]);
    }

    ll ans = 0;
    for (int i = 0; i < res.size(); i++) {
        ans ^= res[i];
    }
    cout << ans << '\n';

    return 0;
}