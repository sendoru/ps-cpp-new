// #include "atcoder/all"
// #pragma GCC optimize("O3,Ofast,unroll-loops")
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

void convolve(vector<ll> &a, vector<ll> &b, ll mod, ll root) {
    int n = a.size() + b.size();
    int log2 = 0;
    while ((1 << log2) < n) {
        log2++;
    }
    n = 1 << log2;

    a.resize(n);
    b.resize(n);

    ntt(a, mod, root);
    ntt(b, mod, root);

    for (int i = 0; i < n; i++) {
        a[i] = (a[i] * b[i]) % mod;
    }

    ntt(a, mod, root, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // stdin from file
    // freopen("input.txt", "r", stdin);

    ll w1, w2, h, th;
    cin >> w1 >> w2 >> h >> th;
    vector<vector<ll>> s(h, vector<ll>(w1)), t(h, vector<ll>(w2));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w1; j++) {
            cin >> s[i][j];
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w2; j++) {
            cin >> t[i][j];
        }
        reverse(t[i].begin(), t[i].end());
    }
    vector<ll> res;
    for (int i = 0; i < h; i++) {
        convolve(s[i], t[i], MOD9, 3);
        if (res.empty()) {
            res = s[i];
        } else {
            for (int j = 0; j < res.size(); j++) {
                res[j] = res[j] + s[i][j];
            }
        }
    }

    ll ans = 0;
    ll start = w2 - 1;
    for (int i = start; i < w1; i++) {
        ans += res[i] > th;
    }

    cout << ans << '\n';

    return 0;
}