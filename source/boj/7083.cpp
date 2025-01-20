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
    vector<int> data, lazy;
    int n;

    LazySegTree(int sz) {
        n = 1;
        while (n < sz) {
            n *= 2;
        }
        data.assign(2 * n, MOD9);
        lazy.assign(2 * n, MOD9);
    }

    LazySegTree(vector<int> &v) {
        int sz = v.size();
        n = 1;
        while (n < sz) {
            n *= 2;
        }
        data.assign(2 * n, MOD9);
        lazy.assign(2 * n, MOD9);
        for (int i = 0; i < sz; i++) {
            data[n + i] = v[i];
        }
        for (int i = n - 1; i > 0; i--) {
            data[i] = min(data[i * 2], data[i * 2 + 1]);
        }
    }

    void propagate(int node, int s, int e) {
        if (lazy[node] != MOD9) {
            data[node] = min(data[node], lazy[node]);
            if (e != s) {
                lazy[node * 2] = min(lazy[node * 2], lazy[node]);
                lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
            }
            lazy[node] = MOD9;
        }
    }

    void update(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val);
    }

    void update(int node, int s, int e, int l, int r, int val) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return;
        }
        if (l <= s && e <= r) {
            lazy[node] = min(lazy[node], val);
            propagate(node, s, e);
            return;
        }
        int mid = (s + e) / 2;
        update(node * 2, s, mid, l, r, val);
        update(node * 2 + 1, mid + 1, e, l, r, val);
        data[node] = min(data[node * 2], data[node * 2 + 1]);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    int query(int node, int s, int e, int l, int r) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return MOD9;
        }
        if (l <= s && e <= r) {
            return data[node];
        }
        int mid = (s + e) / 2;
        return min(query(node * 2, s, mid, l, r), query(node * 2 + 1, mid + 1, e, l, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n, m;
    cin >> n >> m;

    if (m == 0) {
        cout << 0 << endl;
        return 0;
    }

    LazySegTree seg_inner(n + 10), seg_outer(n + 10);
    vector<pii> v(m);
    for (int i = 0; i < m; i++) {
        cin >> v[i].first >> v[i].second;
    }

    int first = v[0].first;
    for (int i = 0; i < m; i++) {
        v[i].first = (v[i].first - first + n) % n;
        v[i].second = (v[i].second - first + n) % n;
    }

    for (int i = 0; i < m; i++) {
        auto [s, e] = v[i];
        int s_c = seg_inner.query(s, s), e_c = seg_inner.query(e, e);
        if (s_c == e_c) {
            seg_inner.update(min(s, e), max(s, e), i);
        } else {
            s_c = seg_outer.query(s, s), e_c = seg_outer.query(e, e);
            if (s_c == e_c) {
                seg_outer.update(min(s, e), max(s, e), i);
            } else {
                cout << i << endl;
                return 0;
            }
        }
    }
    cout << m << endl;
    return 0;
}