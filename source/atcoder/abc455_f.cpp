#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll INV_2 = (MOD9 + 1) / 2;

struct S1 {
    ll val, len;
};

struct S2 {
    ll val, val_square, len;
};

S1 op1(S1 a, S1 b) {
    return {(a.val + b.val) % MOD9, a.len + b.len};
}

S1 e1() {
    return {0, 0};
}

S1 map1(ll f, S1 x) {
    return {(x.val + f * x.len) % MOD9, x.len};
}

ll composition(ll f, ll g) {
    return (f + g) % MOD9;
}

ll id() {
    return 0;
}

S2 op2(S2 a, S2 b) {
    return {(a.val + b.val) % MOD9, (a.val_square + b.val_square) % MOD9, a.len + b.len};
}

S2 e2() {
    return {0, 0, 0};
}

S2 map2(ll f, S2 x) {
    return {(x.val + f * x.len) % MOD9, (x.val_square + 2 * f * x.val + f * f % MOD9 * x.len) % MOD9, x.len};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;

    vector<S1> v1(n, {0, 1});
    vector<S2> v2(n, {0, 0, 1});

    atcoder::lazy_segtree<S1, op1, e1, ll, map1, composition, id> seg1(v1);
    atcoder::lazy_segtree<S2, op2, e2, ll, map2, composition, id> seg2(v2);

    while (q--) {
        ll l, r, a;
        cin >> l >> r >> a;
        l--;
        r--;
        seg1.apply(l, r + 1, a);
        seg2.apply(l, r + 1, a);
        ll sum = seg1.prod(l, r + 1).val;
        ll sum_square = seg2.prod(l, r + 1).val_square;
        cout << (sum * sum % MOD9 - sum_square + MOD9) % MOD9 * INV_2 % MOD9 << "\n";
    }

    return 0;
}