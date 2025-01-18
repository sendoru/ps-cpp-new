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

struct LazySegTree {
    vector<ll> data, lazy;
    ll n;

    LazySegTree(ll sz) {
        n = 1;
        while (n < sz) {
            n *= 2;
        }
        data.assign(2 * n, 0);
        lazy.assign(2 * n, 0);
    }

    LazySegTree(vector<ll> &v) {
        ll sz = v.size();
        n = 1;
        while (n < sz) {
            n *= 2;
        }
        data.assign(2 * n, 0);
        lazy.assign(2 * n, 0);
        for (ll i = 0; i < sz; i++) {
            data[n + i] = v[i];
        }
        for (ll i = n - 1; i > 0; i--) {
            data[i] = data[i * 2] + data[i * 2 + 1];
        }
    }

    void propagate(ll node, ll s, ll e) {
        if (lazy[node] != 0) {
            data[node] += lazy[node] * (e - s + 1);
            if (e != s) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(ll l, ll r, ll diff) {
        update(1, 0, n - 1, l, r, diff);
    }

    void update(ll node, ll s, ll e, ll l, ll r, ll diff) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return;
        }
        if (l <= s && e <= r) {
            lazy[node] += diff;
            propagate(node, s, e);
            return;
        }
        ll mid = (s + e) / 2;
        update(node * 2, s, mid, l, r, diff);
        update(node * 2 + 1, mid + 1, e, l, r, diff);
    }

    ll query(ll l, ll r) {
        return query(1, 0, n - 1, l, r);
    }

    ll query(ll node, ll s, ll e, ll l, ll r) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return 0;
        }
        if (l <= s && e <= r) {
            return data[node];
        }
        ll mid = (s + e) / 2;
        return query(node * 2, s, mid, l, r) + query(node * 2 + 1, mid + 1, e, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;

    vector<ll> a((ll)9e5);
    iota(a.begin(), a.end(), 0);
    LazySegTree seg(a);

    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        ll left = 10e5, right = -1;

        // min left s.t. query(left, left) >= l
        ll binsearch_l = 0, binsearch_r = 8.5e5;
        while (binsearch_l <= binsearch_r) {
            ll mid = (binsearch_l + binsearch_r) / 2;
            ll mid_val = seg.query(mid, mid);
            if (mid_val >= l) {
                left = min(left, mid);
                binsearch_r = mid - 1;
            } else {
                binsearch_l = mid + 1;
            }
        }

        // max right s.t. query(right, right) <= r
        binsearch_l = 0, binsearch_r = 8.5e5;
        while (binsearch_l <= binsearch_r) {
            ll mid = (binsearch_l + binsearch_r) / 2;
            if (seg.query(mid, mid) <= r) {
                right = max(right, mid);
                binsearch_l = mid + 1;
            } else {
                binsearch_r = mid - 1;
            }
        }

        if (left <= right) {
            seg.update(left, right, 1);
        }
    }

    ll q;
    cin >> q;
    while (q--) {
        ll x;
        cin >> x;
        cout << seg.query(x, x) << endl;
    }

    return 0;
}

/*
287946
296269
224599
101453
336997
390315
323363
177075
11431
8580

287940
296263
224593
101449
336991
390287946
296269
224599
101453
336997
310
323355
177068
11431
8580
390315
323363
177075
11431
8580
*/