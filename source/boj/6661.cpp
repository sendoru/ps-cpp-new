// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pdd sum_vector(const pdd &a, const pdd &b) {
    if (a.first == 0.0) {
        return {b.first, b.second};
    }
    if (b.first == 0.0) {
        return {a.first, a.second};
    }
    double x = a.first * cos(a.second * M_PI / 180) + b.first * cos(b.second * M_PI / 180);
    double y = a.first * sin(a.second * M_PI / 180) + b.first * sin(b.second * M_PI / 180);
    double length = sqrt(x * x + y * y);
    double angle = atan2(y, x) * 180 / M_PI;
    return {length, angle};
}

struct LazySegTree {
    // length, angle in degrees
    vector<pdd> tree;
    vector<int> lazy;
    int size;

    template <typename T>
    LazySegTree(vector<T> &v) {
        int n = v.size();
        size = 1;
        while (size <   n) {
            size <<= 1;
        }
        tree.resize(2 * size, {0.0, 0.0});
        lazy.resize(2 * size, 0.0);
        for (int i = 0; i < n; i++) {
            tree[size + i] = {v[i], 90.0};
        }

        for (int i = size - 1; i >= 1; i--) {
            tree[i] = sum_vector(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void update(int l, int r, int angle) {
        update(1, 0, size - 1, l, r, angle);
    }
    pdd update(int node, int s, int e, int l, int r, int angle) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return tree[node];
        }
        if (l <= s && e <= r) {
            tree[node].second += angle;
            tree[node].second = fmod(tree[node].second, 360.0);
            if (s != e) {
                lazy[2 * node] += angle;
                lazy[2 * node] = (lazy[2 * node] + 360) % 360;
                lazy[2 * node + 1] += angle;
                lazy[2 * node + 1] = (lazy[2 * node + 1] + 360) % 360;
            }
            return tree[node];
        }
        int mid = (s + e) / 2;
        pdd left = update(2 * node, s, mid, l, r, angle);
        pdd right = update(2 * node + 1, mid + 1, e, l, r, angle);
        tree[node] = sum_vector(left, right);
        return tree[node];
    }
    void propagate(int node, int s, int e) {
        if (lazy[node] != 0) {
            tree[node].second += lazy[node];
            tree[node].second = fmod(tree[node].second, 360.0);
            if (s != e) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node] = (lazy[2 * node] + 360) % 360;
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 1] = (lazy[2 * node + 1] + 360) % 360;
            }
            lazy[node] = 0;
        }
    }
    pdd query(int l, int r) {
        return query(1, 0, size - 1, l, r);
    }
    pdd query(int node, int s, int e, int l, int r) {
        propagate(node, s, e);
        if (r < s || e < l) {
            return {0.0, 0.0};
        }
        if (l <= s && e <= r) {
            return tree[node];
        }
        int mid = (s + e) / 2;
        pdd left = query(2 * node, s, mid, l, r);
        pdd right = query(2 * node + 1, mid + 1, e, l, r);
        pdd res = sum_vector(left, right);
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        int n, c;
        cin >> n >> c;
        if (!cin.good()) {
            break;
        }

        vector<ll> lengths(n);
        for (int i = 0; i < n; i++) {
            cin >> lengths[i];
        }
        vector<int> angles(n, 0);
        angles[0] = 0;
        LazySegTree segtree(lengths);
        for (int i = 0; i < c; i++) {
            int s, a;
            cin >> s >> a;
            int a_diff = (a + 540 - angles[s]) % 360;
            angles[s] = (a + 540) % 360;
            segtree.update(s, n - 1, a_diff);
            pdd result = segtree.query(0, n - 1);
            cout << fixed;
            cout.precision(2);
            double x = result.first * cos(result.second * M_PI / 180);
            double y = result.first * sin(result.second * M_PI / 180);
            cout << x << " " << y << "\n";
        }
    }

    return 0;
}