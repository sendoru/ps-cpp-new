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

    SegTree(int sz) {
        n = 1;
        while (n < sz) {
            n <<= 1;
        }
        tree.resize(n << 1, 0);
    }

    SegTree(const vector<ll> &v) {
        n = 1;
        while (n < v.size()) {
            n <<= 1;
        }
        tree.resize(n << 1, 0);
        for (int i = 0; i < v.size(); i++) {
            tree[i + n] = v[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i] = tree[i << 1] + tree[(i << 1) | 1];
        }
    }

    void update(int idx, ll val) {
        idx += n;
        tree[idx] = val;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
        }
    }

    ll query(int l, int r) {
        ll res = 0;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                res += tree[l++];
            }
            if (r & 1) {
                res += tree[--r];
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }

    ll query(int idx) {
        return tree[idx + n];
    }

    int lower_bound(ll val) {
        int idx = 1;
        if (tree[idx] < val) {
            return -1;
        }
        while (idx < n) {
            if (tree[idx << 1] >= val) {
                idx <<= 1;
            } else {
                val -= tree[idx << 1];
                idx = (idx << 1) | 1;
            }
        }
        return idx - n;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> w(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<ll> ans;
    SegTree seg(w);
    for (int i = 0; i < n; i++) {
        ll idx = seg.lower_bound(p[i]);
        ans.push_back(idx);
        seg.update(idx, 0);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}