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

    SegTree(int n) : n(n) { tree.resize(4 * n); }

    SegTree(vector<ll> &v)
    {
        n = v.size();
        tree.resize(4 * n);
        init(v, 0, n - 1, 1);
    }

    void init(vector<ll> &v, int left, int right, int node)
    {
        if (left == right) {
            tree[node] = v[left];
            return;
        }

        int mid = (left + right) / 2;
        init(v, left, mid, node * 2);
        init(v, mid + 1, right, node * 2 + 1);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int idx, ll val) { update(1, 0, n - 1, idx, val); }

    void update(int node, int s, int e, int idx, ll val)
    {
        if (idx < s || e < idx) {
            return;
        }

        if (s == e) {
            tree[node] = val;
            return;
        }

        int mid = (s + e) / 2;
        update(node * 2, s, mid, idx, val);
        update(node * 2 + 1, mid + 1, e, idx, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int left, int right) { return query(1, 0, n - 1, left, right); }

    ll query(int node, int s, int e, int left, int right)
    {
        if (right < s || e < left) {
            return 0;
        }

        if (left <= s && e <= right) {
            return tree[node];
        }

        int mid = (s + e) / 2;
        return query(node * 2, s, mid, left, right) +
               query(node * 2 + 1, mid + 1, e, left, right);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // count of triplets (i, j, k) where i < j < k and v[i] > v[j] > v[k]
    SegTree seg1(n + 10), seg2(n + 10);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += seg2.query(v[i] + 1, n);
        seg2.update(v[i], seg2.query(v[i], v[i]) + seg1.query(v[i] + 1, n));
        seg1.update(v[i], seg1.query(v[i], v[i]) + 1);
    }

    cout << ans << '\n';
    return 0;
}