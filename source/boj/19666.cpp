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
    SegTree(int n) : n(n), tree(4 * n) {}

    void update(int i, ll x) {
        update(1, 0, n - 1, i, x);
    }

    void update(int root, int start, int end, int i, ll x) {
        if (i < start || end < i) {
            return;
        }
        if (start == end) {
            tree[root] = x;
            return;
        }
        int mid = (start + end) / 2;
        update(root * 2, start, mid, i, x);
        update(root * 2 + 1, mid + 1, end, i, x);
        tree[root] = tree[root * 2] + tree[root * 2 + 1];
    }

    ll prod(int l, int r) {
        return prod(1, 0, n - 1, l, r);
    }

    ll prod(int root, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[root];
        }
        int mid = (start + end) / 2;
        return prod(root * 2, start, mid, l, r) + prod(root * 2 + 1, mid + 1, end, l, r);
    }

    ll get(int i) {
        return prod(i, i);
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<ll> fact(3 * 1e5 + 10);
    fact[0] = 1;
    for (int i = 1; i < fact.size(); i++) {
        fact[i] = fact[i - 1] * i % MOD1;
    }

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // value compression
    vector<int> sorted_v = v;
    sort(sorted_v.begin(), sorted_v.end());
    for (int i = 0; i < n; i++) {
        v[i] = lower_bound(sorted_v.begin(), sorted_v.end(), v[i]) - sorted_v.begin();
    }

    ll ans = 0;
    SegTree st(n);
    for (int i = n - 1; i >= 0; i--) {
        // ans += (n - i - 1)! * (number of elements smaller than v[i] in the range [i+1, n-1])
        ans += fact[n - i - 1] * st.prod(0, v[i] - 1) % MOD1;
        ans %= MOD1;
        st.update(v[i], 1);
    }

    cout << (ans + 1) % MOD1 << '\n';

    return 0;
}