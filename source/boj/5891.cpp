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

const ll COORD_MAX = 1e6 + 10;

template <typename T, T (*op)(T, T), T (*id)()>
struct SegTree {
    int n;
    vector<T> tree;

    SegTree(int n) : n(n) {
        tree = vector<T>(4 * n, id());
    }

    SegTree(vector<T> &v) {
        n = v.size();
        tree = vector<T>(4 * n, id());
        init(v, 1, 0, n - 1);
    }

    void init(vector<T> &v, int node, int s, int e) {
        if (s == e) {
            tree[node] = v[s];
            return;
        }
        int mid = (s + e) / 2;
        init(v, node * 2, s, mid);
        init(v, node * 2 + 1, mid + 1, e);
        tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int idx, T val) {
        update(1, 0, n - 1, idx, val);
    }

    void update(int node, int s, int e, int idx, T val) {
        if (idx < s || e < idx) {
            return;
        }
        if (s == e) {
            tree[node] = val;
            return;
        }
        int mid = (s + e) / 2;
        update(node * 2, s, mid, idx, val);
        update(node * 2 + 1, mid + 1, e, idx, val);
        tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }

    T prod(int l, int r) {
        return prod(1, 0, n - 1, l, r);
    }

    T prod(int node, int s, int e, int l, int r) {
        if (r < s || e < l) {
            return id();
        }
        if (l <= s && e <= r) {
            return tree[node];
        }

        int mid = (s + e) / 2;
        T prod_l = prod(node * 2, s, mid, l, r);
        T prod_r = prod(node * 2 + 1, mid + 1, e, l, r);
        return op(prod_l, prod_r);
    }
};

ll e_max() {
    return -1e9;
}

ll e_min() {
    return 1e9;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, d;
    cin >> n >> d;

    SegTree<ll, max, e_max> seg_max(COORD_MAX);
    SegTree<ll, min, e_min> seg_min(COORD_MAX);

    vector<ll> xs;

    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        ll min_at_x = seg_min.prod(x, x);
        ll max_at_x = seg_max.prod(x, x);
        if (y > max_at_x) {
            seg_max.update(x, y);
        }
        if (y < min_at_x) {
            seg_min.update(x, y);
        }
        xs.push_back(x);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    ll l = 0, r = COORD_MAX, ans = COORD_MAX;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll cur_diff = 0;
        for (int i : xs) {
            int j = i + mid;
            if (j >= COORD_MAX) {
                j = COORD_MAX - 1;
            }
            cur_diff = max(cur_diff, seg_max.prod(i, j) - seg_min.prod(i, j));
        }
        if (cur_diff >= d) {
            ans = min(ans, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << (ans == COORD_MAX ? -1 : ans);

    return 0;
}