// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct LazySegTree {
    int n;
    vector<ll> tree, lazy;

    LazySegTree(int n) : n(n), tree(4 * n), lazy(4 * n) {}
    LazySegTree(vector<ll> &v) : n(v.size()), tree(4 * n), lazy(4 * n) {
        init(1, 0, n - 1, v);
    }

    void init(int node, int start, int end, vector<ll> &v) {
        if (start == end) {
            if (start < v.size()) {
                tree[node] = v[start];
            }
            return;
        }

        int mid = (start + end) / 2;
        init(node * 2, start, mid, v);
        init(node * 2 + 1, mid + 1, end, v);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int l, int r, ll val) {
        update(1, 0, n - 1, l, r, val);
    }
    void update(int node, int s, int e, int l, int r, ll val) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return;
        }

        if (l <= s && e <= r) {
            tree[node] += (e - s + 1) * val;
            if (s != e) {
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            return;
        }

        int mid = (s + e) / 2;
        update(node * 2, s, mid, l, r, val);
        update(node * 2 + 1, mid + 1, e, l, r, val);
        tree[node] = __gcd(tree[node * 2], tree[node * 2 + 1]);
    }

    void propagate(int node, int s, int e) {
        if (lazy[node] != 0) {
            tree[node] += (e - s + 1) * lazy[node];
            if (s != e) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
    ll query(int node, int s, int e, int l, int r) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return 0;
        }

        if (l <= s && e <= r) {
            return tree[node];
        }

        int mid = (s + e) / 2;
        return query(node * 2, s, mid, l, r) + query(node * 2 + 1, mid + 1, e, l, r);
    }
};

struct GCDSegTree {
    int n;
    vector<ll> tree;
    GCDSegTree(int n) : n(n), tree(4 * n) {}
    GCDSegTree(vector<ll> &v) : n(v.size()), tree(4 * n) {
        init(1, 0, n - 1, v);
    }

    void init(int node, int start, int end, vector<ll> &v) {
        if (start == end) {
            if (start < v.size()) {
                tree[node] = v[start];
            }
            return;
        }

        int mid = (start + end) / 2;
        init(node * 2, start, mid, v);
        init(node * 2 + 1, mid + 1, end, v);

        tree[node] = __gcd(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int idx, ll val) {
        update(1, 0, n - 1, idx, val);
    }

    void update(int node, int s, int e, int idx, ll val) {
        if (idx < s || e < idx) {
            return;
        }

        if (s == e) {
            tree[node] += val;
            return;
        }

        int mid = (s + e) / 2;
        update(node * 2, s, mid, idx, val);
        update(node * 2 + 1, mid + 1, e, idx, val);

        tree[node] = __gcd(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    ll query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) {
            return 0;
        }

        if (l <= s && e <= r) {
            return tree[node];
        }

        int mid = (s + e) / 2;
        return __gcd(query(node * 2, s, mid, l, r), query(node * 2 + 1, mid + 1, e, l, r));
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<ll> diff(n);
    diff[0] = v[0];
    for (int i = 1; i < n; i++) {
        diff[i] = v[i] - v[i - 1];
    }
    LazySegTree lst(v);
    GCDSegTree gst(diff);
    int q;
    cin >> q;
    while (q--) {
        ll t, l, r;
        cin >> t >> l >> r;
        l--;
        r--;
        if (t == 0) {
            ll gcd = gst.query(l + 1, r);
            gcd = __gcd(gcd, lst.query(l, l));
            cout << abs(gcd) << '\n';
        } else {
            lst.update(l, r, t);
            gst.update(l, t);
            if (r < n - 1) {
                gst.update(r + 1, -t);
            }
        }
    }

    return 0;
}