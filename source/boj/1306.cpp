// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

class SegTree {
    int n;
    vector<ll> tree;

  public:
    SegTree(int _n) {
        n = 1;
        while (n < _n) {
            n *= 2;
        }
        tree.resize(2 * n);
    }
    SegTree(const vector<ll> &v) : n(v.size()) {
        while (n < v.size()) {
            n *= 2;
        }
        tree.resize(2 * n);
        for (int i = 0; i < v.size(); i++) {
            tree[n + i] = v[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void update(int idx, ll val) {
        idx += n;
        tree[idx] = val;
        while (idx > 1) {
            idx /= 2;
            tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    ll query(ll l, ll r) {
        l += n;
        r += n;
        ll res = 0;
        while (l < r) {
            if (l & 1) {
                res = max(res, tree[l]);
                l++;
            }
            if (r & 1) {
                r--;
                res = max(res, tree[r]);
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }

    ll query(int idx) {
        return tree[n + idx];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    m = 2 * m - 1;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegTree seg(a);
    for (int i = 0; i + m <= n; i++) {
        cout << seg.query(i, i + m) << ' ';
    }

    return 0;
}