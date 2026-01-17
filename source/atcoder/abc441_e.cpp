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
        while (n < sz)
            n <<= 1;
        tree.resize(2 * n, 0);
    }

    SegTree(vector<ll> &v) {
        int sz = v.size();
        n = 1;
        while (n < sz)
            n <<= 1;
        tree.resize(2 * n, 0);
        for (int i = 0; i < sz; i++) {
            tree[n + i] = v[i];
        }
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void update(int idx, ll val) {
        int node = n + idx;
        tree[node] = val;
        while (node > 1) {
            node >>= 1;
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    ll query(int l, int r) {
        ll res = 0;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                res += tree[l];
                l++;
            }
            if (r & 1) {
                r--;
                res += tree[r];
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    string s;
    cin >> s;
    vector<ll> s_int(n);
    for (int i = 0; i < n; i++) {
        switch (s[i]) {
        case 'A':
            s_int[i] = 1;
            break;
        case 'B':
            s_int[i] = -1;
            break;
        case 'C':
            s_int[i] = 0;
            break;
        }
    }
    vector<ll> pf_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pf_sum[i + 1] = pf_sum[i] + s_int[i];
    }
    // make sure all values are non-negative
    for (int i = 0; i < n + 1; i++) {
        pf_sum[i] += n;
    }

    SegTree seg(2 * n + 2);
    ll ans = 0;
    for (int i = 1; i < n + 1; i++) {
        seg.update(pf_sum[i], seg.query(pf_sum[i], pf_sum[i] + 1) + 1);
    }

    for (int i = 0; i < n; i++) {
        ans += seg.query(pf_sum[i] + 1, 2 * n + 2);
        seg.update(pf_sum[i + 1], seg.query(pf_sum[i + 1], pf_sum[i + 1] + 1) - 1);
    }

    cout << ans;

    return 0;
}