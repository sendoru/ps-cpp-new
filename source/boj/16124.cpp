// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll a, ll b, ll mod) {
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

struct LazySegTree {
    int n;
    vector<pll> tree;
    vector<ll> lazy;

    LazySegTree(int n) : n(n), tree(4 * n), lazy(4 * n) {}
    LazySegTree(vector<ll> &v) : n(v.size()), tree(4 * n), lazy(4 * n) {
        init(1, 0, n - 1, v);
    }

    pll init(int node, int start, int end, vector<ll> &v) {
        if (start == end) {
            if (start < v.size()) {
                tree[node] = {v[start], 1};
            }
            return tree[node];
        }

        int mid = (start + end) / 2;
        pll node_l = init(node * 2, start, mid, v);
        pll node_r = init(node * 2 + 1, mid + 1, end, v);
        ll node_val = (node_l.first + node_r.first * modpow(10, node_l.second, MOD9)) % MOD9;
        ll node_size = node_l.second + node_r.second;

        tree[node] = {node_val, node_size};
    }

    void update(int l, int r, ll val) {
        update(1, 0, n - 1, l, r, val);
    }
    pll update(int node, int s, int e, int l, int r, ll val) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return;
        }

        if (l <= s && e <= r) {
            // tree[node].first = val + 10val + ... + 1e(size-1)val
            // tree[node].first = val * (1 + 10 + ... + 10^(size-1))
            // tree[node].first = val * (10^size - 1) / 9
            ll tree_val = (modpow(10, tree[node].second, MOD9) - 1) * modpow(9, MOD9 - 2, MOD9) % MOD9 * val % MOD9;
            tree[node] = {tree_val, tree[node].second};
            if (s != e) {
                lazy[node * 2] = val;
                lazy[node * 2 + 1] = val;
            }
            return;
        }

        int mid = (s + e) / 2;
        pll node_l = update(node * 2, s, mid, l, r, val);
        pll node_r = update(node * 2 + 1, mid + 1, e, l, r, val);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        ll node_val = (node_l.first + node_r.first * modpow(10, node_l.second, MOD9)) % MOD9;
        ll node_size = node_l.second + node_r.second;

        tree[node] = {node_val, node_size};
        return tree[node];
    }

    void propagate(int node, int s, int e) {
        if (lazy[node] != MOD1) {
            ll tree_val = (modpow(10, tree[node].second, MOD9) - 1) * modpow(9, MOD9 - 2, MOD9) % MOD9 * lazy[node] % MOD9;
            tree[node] = {tree_val, tree[node].second};
            if (s != e) {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = MOD1;
        }
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
    ll query(int node, int s, int e, int l, int r) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return MOD1;
        }

        if (l <= s && e <= r) {
            return tree[node].first;
        }

        int mid = (s + e) / 2;
        return min(query(node * 2, s, mid, l, r), query(node * 2 + 1, mid + 1, e, l, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    LazySegTree seg(s.length() + 1);
    vector<ll> v(s.length());
    for (int i = 0; i < s.length(); i++) {
        v[i] = s[i] - '0';
    }
    seg.init(1, 0, s.length() - 1, v);

    int q;
    cin >> q;
}