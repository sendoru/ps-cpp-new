#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct S {
    ll a, size;
};

struct F {
    ll add, mul;
    F() {
        add = 0;
        mul = 1;
    }
    F(ll _add, ll _mul) {
        add = _add;
        mul = _mul;
    }
};

S op(S a, S b) { return S{(a.a + b.a) % MOD9, a.size + b.size}; }
S e() { return S{0, 0}; }
S mapping(F f, S a) {
    return S{((a.a * f.mul) % MOD9 + (a.size * f.add) % MOD9) % MOD9, a.size};
}
F id() { return F(0, 1); }
F compose(F f, F g) {
    // f(g)를 구해야 됨
    return F((f.mul * g.add % MOD9 + f.add) % MOD9, f.mul * g.mul % MOD9);
}

ll op_sum(ll a, ll b) {
    return (a + b) % MOD9;
}

ll e_sum() {
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<array<ll, 2>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }

    // the problem is talking about scc,
    // but its equal to find the number of ways to pick intervals so [0, n) is covered.
    sort(edges.begin(), edges.end(), [](const array<ll, 2> &a, const array<ll, 2> &b) {
        if (a[0] == b[0]) {
            return a[1] > b[1];
        }
        return a[0] < b[0];
    });
    vector<S> dp_init(n + 1);
    for (int i = 0; i <= n; i++) {
        dp_init[i] = S{0, 1};
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, compose, id> dp(dp_init);
    dp.set(1, S{1, 1});
    for (auto [l, r] : edges) {
        ll sum = dp.prod(l, r + 1).a;
        dp.apply(r + 1, n + 1, F(0, 2));
        dp.apply(r, r + 1, F(sum, 1));
    }

    cout << dp.get(n).a << "\n";
    return 0;
}