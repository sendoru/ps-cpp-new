// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    vector<int> parent;
    vector<int> min_element;
    vector<int> max_element;

    Dsu(int n, vector<int> &elems) {
        parent.resize(n);
        min_element.resize(n);
        max_element.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            min_element[i] = elems[i];
            max_element[i] = elems[i];
        }
    }

    int find(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a > b) {
            swap(a, b);
        }
        if (a != b) {
            parent[b] = a;
            min_element[a] = min(min_element[a], min_element[b]);
            max_element[a] = max(max_element[a], max_element[b]);
        }
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int get_min(int v) {
        return min_element[find(v)];
    }

    int get_max(int v) {
        return max_element[find(v)];
    }
};

struct MaxSegTree {
    int n;
    vector<int> tree;

    MaxSegTree(int n) : n(n) {
        tree.resize(4 * n);
    }

    void update(int v, int idx) {
        update(1, 0, n - 1, idx, v);
    }

    void update(int root, int l, int r, int idx, int v) {
        if (l == r) {
            tree[root] = v;
            return;
        }

        int m = (l + r) / 2;
        if (idx <= m) {
            update(2 * root, l, m, idx, v);
        } else {
            update(2 * root + 1, m + 1, r, idx, v);
        }

        tree[root] = max(tree[2 * root], tree[2 * root + 1]);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    int query(int root, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[root];
        }
        int mid = (start + end) / 2;
        return max(query(root * 2, start, mid, l, r), query(root * 2 + 1, mid + 1, end, l, r));
    }
};

vector<int>
solve(vector<int> &h) {
    int n = h.size();
    reverse(h.begin(), h.end());
    MaxSegTree seg_tree(n);
    for (int i = 0; i < n; i++) {
        seg_tree.update(h[i], i);
    }

    // max_right_idx[i]: the greatest index j such that h[j] is bigger than current h[i]

    vector<int> max_right_idx(n);
    for (int i = 0; i < n; i++) {
        int l = i + 1, r = n - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            int query = seg_tree.query(m, n - 1);
            if (query > h[i]) {
                max_right_idx[i] = max(max_right_idx[i], m);
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        max_right_idx[i] = max(max_right_idx[i], i);
    }

    Dsu dsu(n, h);
    int next_max_right_idx = max_right_idx[0];
    vector<int> ans(n);
    for (int i = 0; i < n;) {
        next_max_right_idx = max(next_max_right_idx, max_right_idx[i]);
        for (int j = i; j <= next_max_right_idx - 1; j++) {
            dsu.unite(j, j + 1);
            next_max_right_idx = max(next_max_right_idx, max_right_idx[j]);
        }
        i = next_max_right_idx + 1;
    }

    for (int i = 0; i < n; i++) {
        ans[i] = dsu.get_max(i);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> h(n);
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }

        vector<int> ans = solve(h);
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << '\n';
    }

    return 0;
}