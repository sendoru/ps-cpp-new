// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct MinSegTree {
    int n;
    vector<ll> tree;

    MinSegTree(int n) : n(n), tree(4 * n, 1e12) {}
    MinSegTree(int n, ll init_val) {
        this->n = n;
        tree.resize(4 * n);
        fill(tree.begin(), tree.end(), init_val);
    }
    MinSegTree(vector<ll> &v) {
        n = v.size();
        tree.resize(4 * n);
        init(v, 0, n - 1, 1);
    }
    void init(vector<ll> &v, int left, int right, int node) {
        if (left == right) {
            tree[node] = v[left];
            return;
        }
        int mid = (left + right) / 2;
        init(v, left, mid, node * 2);
        init(v, mid + 1, right, node * 2 + 1);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    void update(int root, int l, int r, int idx, int val) {
        if (idx < l || r < idx)
            return;
        if (l == r) {
            tree[root] = val;
            return;
        }
        int mid = (l + r) / 2;
        update(root * 2, l, mid, idx, val);
        update(root * 2 + 1, mid + 1, r, idx, val);
        tree[root] = min(tree[root * 2], tree[root * 2 + 1]);
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    ll query(int root, int s, int e, int l, int r) {
        if (r < s || e < l)
            return 1e12;
        if (l <= s && e <= r)
            return tree[root];
        int mid = (s + e) / 2;
        return min(query(root * 2, s, mid, l, r), query(root * 2 + 1, mid + 1, e, l, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    MinSegTree st_start(2 * n + 2), st_end(2 * n + 2);

    vector<pii> lrs(n);
    for (int i = 0; i < n; i++) {
        cin >> lrs[i].first >> lrs[i].second;
        if (st_start.query(lrs[i].first, lrs[i].first) >= w[i])
            st_start.update(lrs[i].first, w[i]);
        if (st_end.query(lrs[i].second, lrs[i].second) >= w[i])
            st_end.update(lrs[i].second, w[i]);
    }

    int q;
    cin >> q;
    while (q--) {
        int s, t;
        cin >> s >> t;
        s--;
        t--;
        if (lrs[s].first > lrs[t].first) {
            swap(s, t);
        }

        if (lrs[s].second < lrs[t].first) {
            cout << w[s] + w[t] << '\n';
        }

        else {
            ll ans = 1e12;

            int all_max = max(lrs[s].second, lrs[t].second);
            ll left_min = st_end.query(0, lrs[s].first - 1);
            ll right_min = st_start.query(all_max + 1, 2 * n + 1);
            ans = w[s] + w[t] + min(left_min, right_min);

            if (lrs[t].second > lrs[s].second) {
                left_min = st_end.query(0, lrs[t].first - 1);
                right_min = st_start.query(lrs[s].second + 1, 2 * n + 1);
                ans = min(ans, w[s] + w[t] + left_min + right_min);
            }

            if (ans >= 1e12) {
                cout << -1 << '\n';
            } else {
                cout << ans << '\n';
            }
        }
    }

    return 0;
}