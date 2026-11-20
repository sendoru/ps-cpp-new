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

    void update(int idx, ll val) {
        idx += n;
        tree[idx] += val;
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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    ll res = 0;
    SegTree seg(n);
    for (int i = 0; i < n; i++) {
        res += seg.query(a[i] + 1, n);
        seg.update(a[i], 1);
    }

    cout << res;

    return 0;
}