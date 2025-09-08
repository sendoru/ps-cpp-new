// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct SegTree {
    int n;
    vector<ll> tree;
    function<ll(ll, ll)> merge;
    ll id;
    SegTree(int size, function<ll(ll, ll)> _merge, ll _id) {
        n = 1;
        while (n < size)
            n *= 2;
        tree.resize(2 * n, _id);
        merge = _merge;
        id = _id;
    }
    void update(int idx, ll val) {
        idx += n;
        tree[idx] = val;
        while (idx > 1) {
            idx /= 2;
            tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
        }
    }
    ll prod(int l, int r) {
        ll res = id;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1)
                res = merge(res, tree[l++]);
            if (r & 1)
                res = merge(tree[--r], res);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    ll get(int idx) {
        return tree[idx + n];
    }
};

// 구간 min 업데이트 + 구간 max 쿼리
struct MinMaxLazySegTree {
    int n;
    vector<ll> tree, lazy;

    MinMaxLazySegTree(int size) {
        n = 1;
        while (n < size)
            n *= 2;
        tree.resize(2 * n, LLONG_MAX);
        lazy.resize(2 * n, LLONG_MAX);
    }

    void prop(int node, int l, int r) {
        if (lazy[node] != LLONG_MAX) {
            tree[node] = min(tree[node], lazy[node]);
            if (l + 1 < r) {
                lazy[2 * node] = min(lazy[2 * node], lazy[node]);
                lazy[2 * node + 1] = min(lazy[2 * node + 1], lazy[node]);
            }
            lazy[node] = LLONG_MAX;
        }
    }

    ll prod(int l, int r) {
        return prod(l, r, 1, 0, n);
    }

    ll prod(int l, int r, int node, int s, int e) {
        prop(node, s, e);
        if (r <= s || e <= l)
            return LLONG_MIN;
        if (l <= s && e <= r)
            return tree[node];
        int m = (s + e) / 2;
        return max(prod(l, r, 2 * node, s, m), prod(l, r, 2 * node + 1, m, e));
    }

    void update(int l, int r, ll val) {
        update(l, r, val, 1, 0, n);
    }

    void update(int l, int r, ll val, int node, int s, int e) {
        prop(node, s, e);
        if (r <= s || e <= l)
            return;
        if (l <= s && e <= r) {
            lazy[node] = min(lazy[node], val);
            prop(node, s, e);
            return;
        }
        int m = (s + e) / 2;
        update(l, r, val, 2 * node, s, m);
        update(l, r, val, 2 * node + 1, m, e);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
        vector<ll> a(n + 1), l(n + 1), r(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> l[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> r[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        MinMaxLazySegTree st(n + 2);
        vector<ll> dp(n + 2);
        dp[n + 1] = 0;
        st.update(n + 1, n + 2, 0);
        for (int i = n; i >= 1; i--) {
            ll val = st.prod(min((ll)n + 1, i + l[i]), min((ll)n + 2, i + r[i] + 1));
            dp[i] = val;
            st.update(i, min(n + 1, i + c + 1), val + a[i]);
        }
        cout << dp[1] << "\n";
    }

    return 0;
}