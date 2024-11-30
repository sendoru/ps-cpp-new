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
    LazySegTree(int n, int val) {
        this->n = n;
        tree.assign(4 * n, val);
        lazy.assign(4 * n, val);
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

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
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
            tree[node] = val;
            if (s != e) {
                lazy[node * 2] = val;
                lazy[node * 2 + 1] = val;
            }
            return;
        }

        int mid = (s + e) / 2;
        update(node * 2, s, mid, l, r, val);
        update(node * 2 + 1, mid + 1, e, l, r, val);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void propagate(int node, int s, int e) {
        if (lazy[node] != MOD1) {
            tree[node] = lazy[node];
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
            return tree[node];
        }

        int mid = (s + e) / 2;
        return min(query(node * 2, s, mid, l, r), query(node * 2 + 1, mid + 1, e, l, r));
    }
};

struct bar {
    int r, c, l, idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int h, w, n;
    cin >> h >> w >> n;
    vector<bar> bars(n);
    for (int i = 0; i < n; i++) {
        cin >> bars[i].r >> bars[i].c >> bars[i].l;
        bars[i].idx = i;
    }

    sort(bars.begin(), bars.end(), [](const bar &a, const bar &b) {
        return a.r > b.r;
    });

    vector<int> ans(n);
    LazySegTree st(w + 10, h);

    for (int i = 0; i < n; i++) {
        int val = st.query(bars[i].c, bars[i].c + bars[i].l - 1);
        ans[bars[i].idx] = val;
        st.update(bars[i].c, bars[i].c - 1 + bars[i].l, val - 1);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}