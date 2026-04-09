// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// range add (only positive) update + range max query
struct LazySegTree {
    int n;
    vector<ll> data, lazy;

    LazySegTree(ll _n) {
        ll log2n = 0;
        while ((1ll << log2n) < _n) {
            log2n++;
        }
        n = 1ll << log2n;
        data.assign(2 * n, 0);
        lazy.assign(2 * n, 0);
    }

    LazySegTree(const vector<ll> &v) : LazySegTree(v.size()) {
        for (int i = 0; i < v.size(); i++) {
            data[n + i] = v[i];
        }
        for (int i = n - 1; i > 0; i--) {
            data[i] = max(data[2 * i], data[2 * i + 1]);
        }
    }

    void update(int l, int r, ll val) {
        update(l, r, val, 1, 0, n);
    }

    void update(int l, int r, ll val, int node, int node_l, int node_r) {
        if (r <= node_l || node_r <= l) {
            return;
        }
        if (l <= node_l && node_r <= r) {
            data[node] += val;
            lazy[node] += val;
            return;
        }
        push(node, node_l, node_r);
        int mid = (node_l + node_r) / 2;
        update(l, r, val, 2 * node, node_l, mid);
        update(l, r, val, 2 * node + 1, mid, node_r);
        data[node] = max(data[2 * node], data[2 * node + 1]);
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0) {
            return;
        }
        int mid = (l + r) / 2;
        data[2 * node] += lazy[node];
        lazy[2 * node] += lazy[node];
        data[2 * node + 1] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
        lazy[node] = 0;
    }

    ll query(int l, int r) {
        return query(l, r, 1, 0, n);
    }

    ll query(int l, int r, int node, int node_l, int node_r) {
        if (r <= node_l || node_r <= l) {
            return -1e12;
        }
        if (l <= node_l && node_r <= r) {
            return data[node];
        }
        push(node, node_l, node_r);
        int mid = (node_l + node_r) / 2;
        return max(query(l, r, 2 * node, node_l, mid), query(l, r, 2 * node + 1, mid, node_r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<ll> c(n + k + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    n += k;

    vector<ll> dp(n + 1);
    ll seg0 = 0;
    vector<int> last_seen(k + 1, -1);
    for (int i = 1; i < (k + 1) / 2; i++) {
        dp[i] = -1e12;
        if (c[i] != 0) {
            if (last_seen[c[i]] == -1) {
                seg0++;
            }
            last_seen[c[i]] = i;
        }
    }
    LazySegTree seg(dp);
    seg.update(0, 1, seg0);
    for (int i = (k + 1) / 2; i <= n; i++) {
        if (c[i] != 0) {
            seg.update(last_seen[c[i]], i + 1, 1);
            last_seen[c[i]] = i;
        }
        dp[i] = seg.query(0, i - (k + 1) / 2 + 1);
        seg.update(i, i + 1, dp[i] - seg.query(i, i + 1));
    }

    cout << dp.back() << "\n";

    return 0;
}