// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct DynamicSegTree {
    ll n;
    struct Node {
        ll val;
        Node *l, *r;
        Node(ll val) : val(val), l(nullptr), r(nullptr) {}
        Node(ll val, Node *l, Node *r) : val(val), l(l), r(r) {}
    };
    Node *root;

    DynamicSegTree(ll n) : n(n), root(new Node(0)) {}

    void update(ll idx, ll val) {
        update(root, 0, n - 1, idx, val);
    }

    void update(Node *node, ll s, ll e, ll idx, ll val) {
        if (s == e) {
            node->val = val;
            return;
        }
        int m = (s + e) >> 1;
        if (idx <= m) {
            if (!node->l) {
                node->l = new Node(0);
            }
            update(node->l, s, m, idx, val);
        } else {
            if (!node->r) {
                node->r = new Node(0);
            }
            update(node->r, m + 1, e, idx, val);
        }
        ll l_val = node->l ? node->l->val : 0;
        ll r_val = node->r ? node->r->val : 0;
        node->val = max(l_val, r_val);
    }

    ll query(ll l, ll r) {
        return query(root, 0, n - 1, l, r);
    }

    ll query(Node *root, ll s, ll e, ll l, ll r) {
        if (!root || r < s || e < l) {
            return 0;
        }
        if (l <= s && e <= r) {
            return root->val;
        }
        ll mid = (s + e) / 2;
        return max(query(root->l, s, mid, l, r), query(root->r, mid + 1, e, l, r));
    }

    ~DynamicSegTree() {
        clear(root);
    }

    void clear(Node *node) {
        if (!node) {
            return;
        }
        clear(node->l);
        clear(node->r);
        delete node;
    }
};

struct SegTree {
    int n;
    vector<ll> tree;
    SegTree(int n) : n(n), tree(4 * n) {}
    SegTree(vector<ll> &v) : n(v.size()), tree(4 * n) {
        init(1, 0, n - 1, v);
    }

    void init(int node, int start, int end, vector<ll> &v) {
        if (start == end) {
            if (start < v.size()) {
                tree[node] = v[start];
            }
            return;
        }

        int mid = (start + end) / 2;
        init(node * 2, start, mid, v);
        init(node * 2 + 1, mid + 1, end, v);

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int idx, ll val) {
        update(1, 0, n - 1, idx, val);
    }

    void update(int node, int s, int e, int idx, ll val) {
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

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    ll query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) {
            return 0;
        }

        if (l <= s && e <= r) {
            return tree[node];
        }

        int mid = (s + e) / 2;
        return max(query(node * 2, s, mid, l, r), query(node * 2 + 1, mid + 1, e, l, r));
    }
};

// get the maximum lenght of subsequence (not necessarily contiguous)
// where the difference of adjacent elements is diff or less
ll solve(vector<ll> &v_compressed, vector<ll> &v_unique_sorted, SegTree &seg, ll diff) {
    int n = v_compressed.size();
    vector<ll> dp(n, 1);
    seg.update(v_compressed[0], 1);

    for (int i = 1; i < n; i++) {
        // the inner loop should be optimized
        // for (int j = 0; j < i; j++) {
        //     if (abs(v[i] - v[j]) <= diff) {
        //         dp[i] = max(dp[i], dp[j] + 1);
        //     }
        // }
        ll l = lower_bound(
                   v_unique_sorted.begin(),
                   v_unique_sorted.end(),
                   v_unique_sorted[v_compressed[i]] - diff) -
               v_unique_sorted.begin();
        ll r = upper_bound(
                   v_unique_sorted.begin(),
                   v_unique_sorted.end(),
                   v_unique_sorted[v_compressed[i]] + diff) -
               v_unique_sorted.begin() - 1;
        dp[i] = seg.query(l, r) + 1;
        seg.update(v_compressed[i], max(dp[i], seg.query(v_compressed[i], v_compressed[i])));
    }
    for (int i = 0; i < n; i++) {
        seg.update(v_compressed[i], 0);
    }
    return *max_element(dp.begin(), dp.end());
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, x;
    cin >> n >> x;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<ll> v_unique_sorted = v;
    sort(v_unique_sorted.begin(), v_unique_sorted.end());
    v_unique_sorted.erase(unique(v_unique_sorted.begin(), v_unique_sorted.end()), v_unique_sorted.end());

    vector<ll> v_compressed = v;
    for (int i = 0; i < n; i++) {
        v_compressed[i] = lower_bound(v_unique_sorted.begin(), v_unique_sorted.end(), v[i]) - v_unique_sorted.begin();
    }

    SegTree seg(v_unique_sorted.size());

    ll ans = 1e10;
    ll l = 0, r = 1e9 + 10;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (solve(v_compressed, v_unique_sorted, seg, m) >= x) {
            ans = min(ans, m);
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}
