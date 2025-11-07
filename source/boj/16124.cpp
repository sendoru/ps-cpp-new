// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll pow10mod[1'000'010];

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
    vector<pair<array<ll, 10>, ll>> tree;
    vector<array<int, 10>> lazy;

    LazySegTree(int n) : n(n), tree(4 * n), lazy(4 * n) {
        for (auto &arr : lazy) {
            for (int i = 0; i < 10; i++) {
                arr[i] = i;
            }
        }
    }
    LazySegTree(vector<ll> &v) : n(v.size()), tree(4 * n), lazy(4 * n) {
        for (auto &arr : lazy) {
            for (int i = 0; i < 10; i++) {
                arr[i] = i;
            }
        }
        init(1, 0, n - 1, v);
    }

    pair<array<ll, 10>, ll> init(int node, int start, int end, vector<ll> &v) {
        if (start == end) {
            if (start < v.size()) {
                tree[node].first[v[start]] = 1;
                tree[node].second = 1;
            }
            return tree[node];
        }

        int mid = (start + end) / 2;
        auto node_l = init(node * 2, start, mid, v);
        auto node_r = init(node * 2 + 1, mid + 1, end, v);
        array<ll, 10> node_val = {};
        for (int i = 0; i < 10; i++) {
            node_val[i] = (node_l.first[i] * pow10mod[node_r.second] + node_r.first[i]) % MOD9;
        }
        ll node_size = node_l.second + node_r.second;

        tree[node] = {node_val, node_size};
        return tree[node];
    }

    void update(int l, int r, ll from, ll to) {
        update(1, 0, n - 1, l, r, from, to);
    }

    pair<array<ll, 10>, ll> update(int node, int s, int e, int l, int r, ll from, ll to) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return tree[node];
        }

        if (l <= s && e <= r) {
            array<ll, 10> node_arr = tree[node].first;
            ll temp = tree[node].first[from];
            node_arr[to] = (node_arr[to] + temp) % MOD9;
            node_arr[from] = (node_arr[from] - temp + MOD9) % MOD9;
            tree[node] = {node_arr, tree[node].second};
            if (s != e) {
                for (int i = 0; i < 10; i++) {
                    if (lazy[node * 2][i] == from) {
                        lazy[node * 2][i] = to;
                    }
                    if (lazy[node * 2 + 1][i] == from) {
                        lazy[node * 2 + 1][i] = to;
                    }
                }
            }
            return tree[node];
        }

        int mid = (s + e) / 2;
        auto node_l = update(node * 2, s, mid, l, r, from, to);
        auto node_r = update(node * 2 + 1, mid + 1, e, l, r, from, to);

        array<ll, 10> node_val = {};
        for (int i = 0; i < 10; i++) {
            node_val[i] = (node_l.first[i] * pow10mod[node_r.second] + node_r.first[i]) % MOD9;
        }
        ll node_size = node_l.second + node_r.second;
        tree[node] = {node_val, node_size};
        return tree[node];
    }

    void propagate(int node, int s, int e) {
        if (lazy[node] != array<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
            array<ll, 10> node_arr = tree[node].first;
            for (int i = 0; i < 10; i++) {
                ll cur = node_arr[i];
                tree[node].first[i] = (tree[node].first[i] - cur + MOD9) % MOD9;
                tree[node].first[lazy[node][i]] = (tree[node].first[lazy[node][i]] + cur) % MOD9;
            }
            if (s != e) {
                for (int i = 0; i < 10; i++) {
                    lazy[node * 2][i] = lazy[node][lazy[node * 2][i]];
                    lazy[node * 2 + 1][i] = lazy[node][lazy[node * 2 + 1][i]];
                }
            }
            lazy[node] = array<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        }
    }

    ll query(int l, int r) {
        auto q_res = query(1, 0, n - 1, l, r);
        ll res = 0;
        for (int i = 0; i < 10; i++) {
            res = (res + i * q_res.first[i]) % MOD9;
        }
        return res;
    }
    pair<array<ll, 10>, ll> query(int node, int s, int e, int l, int r) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return {array<ll, 10>{}, 0};
        }

        if (l <= s && e <= r) {
            return tree[node];
        }

        int mid = (s + e) / 2;
        auto node_l = query(node * 2, s, mid, l, r);
        auto node_r = query(node * 2 + 1, mid + 1, e, l, r);
        array<ll, 10> node_val = {};
        for (int i = 0; i < 10; i++) {
            node_val[i] = (node_l.first[i] * pow10mod[node_r.second] + node_r.first[i]) % MOD9;
        }
        ll node_size = node_l.second + node_r.second;
        return {node_val, node_size};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pow10mod[0] = 1;
    for (int i = 1; i <= 1'000'010; i++) {
        pow10mod[i] = (pow10mod[i - 1] * 10) % MOD9;
    }

    string s;
    cin >> s;
    LazySegTree seg(s.length());
    vector<ll> v(s.length());
    for (int i = 0; i < s.length(); i++) {
        v[i] = s[i] - '0';
    }
    seg.init(1, 0, s.length() - 1, v);

    int q;
    cin >> q;

    while (q--) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            int l, r, from, to;
            cin >> l >> r >> from >> to;
            l--;
            r--;
            seg.update(l, r, from, to);
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << seg.query(l, r) << '\n';
        }
    }

    return 0;
}