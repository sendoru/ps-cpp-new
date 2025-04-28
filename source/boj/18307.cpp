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

struct SegTree {
    int n;
    vector<ll> tree;

    SegTree(int n) : n(n), tree(4 * n) {}
    SegTree(const vector<ll> &a) : n(a.size()), tree(4 * n) {
        build(a, 0, 0, n - 1);
    }

    void build(const vector<ll> &a, int node, int start, int end) {
        if (start == end) {
            tree[node] = a[start];
        } else {
            int mid = (start + end) / 2;
            build(a, 2 * node + 1, start, mid);
            build(a, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    ll query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    ll query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return query(2 * node + 1, start, mid, l, r) + query(2 * node + 2, mid + 1, end, l, r);
    }

    void update(int idx, ll val) {
        update(0, 0, n - 1, idx, val);
    }

    void update(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pdd x1 = {sqrt(3), -1}, x2 = {-sqrt(3), -1};

    int n;
    cin >> n;
    vector<pdd> dots(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        dots[i].first = x / sqrt(3) - y;
        dots[i].second = -x / sqrt(3) - y;
    }

    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) {
        x[i] = dots[i].first;
        y[i] = dots[i].second;
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());

    for (int i = 0; i < n; i++) {
        dots[i].first = lower_bound(x.begin(), x.end(), dots[i].first) - x.begin();
        dots[i].second = lower_bound(y.begin(), y.end(), dots[i].second) - y.begin();
    }

    // get count of pair (p1, p2) st. p1.first < p2.first and p1.second < p2.second

    sort(dots.begin(), dots.end());
    SegTree seg(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += seg.query(0, dots[i].second);
        seg.update(dots[i].second, seg.query(dots[i].second, dots[i].second) + 1);
    }

    cout << ans << '\n';

    return 0;
}