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

    SegTree(int size) {
        n = 1;
        while (n < size)
            n <<= 1;
        tree.assign(2 * n, 0);
    }

    void update(int idx, ll val) {
        idx += n;
        tree[idx] += val;
        tree[idx] %= MOD1;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
            tree[idx] %= MOD1;
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
            res %= MOD1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (k == 1) {
        cout << n;
        return 0;
    }

    vector<SegTree> trees(k, SegTree(n + 10));
    ll ans = 0;
    for (auto elem : a) {
        trees[0].update(elem, 1);
        for (int i = 1; i < k; i++) {
            ll val = trees[i - 1].query(0, elem);
            trees[i].update(elem, val);
            if (i == k - 1) {
                ans += val;
                ans %= MOD1;
            }
        }
    }

    cout << ans;

    return 0;
}