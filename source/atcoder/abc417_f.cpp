#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll a, ll b, ll mod)
{
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

ll modinv(ll a, ll mod)
{
    return modpow(a, mod - 2, mod);
}

// some functions for range add and mul lazy segment tree
struct S {
    ll val, size;
};

struct F {
    ll a, b;
    F()
    {
        a = 1;
        b = 0;
    }
    F(ll a, ll b) : a(a), b(b) {}
};

S op(S x, S y)
{
    return {(x.val + y.val) % MOD9, x.size + y.size};
}

S e()
{
    return {0, 0};
}

S mapping(F f, S x)
{
    return {(x.val * f.a + x.size * f.b) % MOD9, x.size};
};

F id()
{
    return F();
}

F compose(F f, F g)
{
    return {f.a * g.a % MOD9, (f.a * g.b + f.b) % MOD9};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, compose, id> segtree(n);
    for (int i = 0; i < n; i++) {
        segtree.set(i, {a[i], 1});
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        S res = segtree.prod(l, r + 1);
        ll range_sum = res.val;
        ll to_add = range_sum * modinv(r - l + 1, MOD9) % MOD9;
        segtree.apply(l, r + 1, F(0, to_add));
    }
    for (int i = 0; i < n; i++) {
        cout << segtree.get(i).val << " ";
    }

    return 0;
}