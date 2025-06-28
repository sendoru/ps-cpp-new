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
        while (n <= sz) {
            n *= 2;
        }
        tree.resize(2 * n, 0);
    }

    void update(int idx, ll val) {
        idx += n;
        tree[idx] = val;
        while (idx > 1) {
            idx /= 2;
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }

    ll query(int l, int r) {
        l += n;
        r += n;
        ll res = 0;
        while (l < r) {
            if (l % 2 == 1) {
                res += tree[l];
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res += tree[r];
            }
            l /= 2;
            r /= 2;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> a_unique = a;
    sort(a_unique.begin(), a_unique.end());
    a_unique.erase(unique(a_unique.begin(), a_unique.end()), a_unique.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(a_unique.begin(), a_unique.end(), a[i]) - a_unique.begin();
    }

    SegTree seg(n);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += seg.query(a[i] + 1, n) + 1;
        seg.update(a[i], seg.query(a[i], a[i] + 1) + 1);
    }

    cout.precision(10);
    cout << (double)ans / n << '\n';

    return 0;
}