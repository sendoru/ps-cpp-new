// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct MinSegTree {
    vector<int> tree;
    int size;

    MinSegTree(int n) {
        size = n;
        tree.resize(4 * n, 1e9);
    }

    void update(int idx, int val) {
        update(1, 0, size - 1, idx, val);
    }

    int query(int l, int r) {
        return query(1, 0, size - 1, l, r);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = min(tree[node], val);
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 1e9;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return min(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, d;
    cin >> n >> d;

    vector<int> a(n);
    vector<vector<int>> quot_by_mod(d);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (d == 0) {
        vector<int> cnt(1e6 + 1, 0);
        for (int i = 0; i < n; i++) {
            cnt[a[i]]++;
        }
        int ans = 0;
        for (int i = 0; i <= 1e6; i++) {
            ans += max(0, cnt[i] - 1);
        }
        cout << ans << '\n';
        return 0;
    }

    for (int i = 0; i < n; i++) {
        quot_by_mod[a[i] % d].push_back(a[i] / d);
    }

    for (auto &v : quot_by_mod) {
        sort(v.begin(), v.end());
    }

    int ans = 0;
    for (auto &a : quot_by_mod) {
        if (a.size() == 0) {
            continue;
        }
        vector<int> dp(a.size(), INT_MAX);
        MinSegTree seg(a.back() + 1);
        dp[0] = 0;
        seg.update(a[0], 0);
        for (int i = 1; i < a.size(); i++) {
            dp[i] = i;
            // 0 ~ a[i] - d - 1
            if (a[i] - 2 >= 0)
                dp[i] = min(dp[i], seg.query(0, a[i] - 2) + i - 1);

            // a[i] - d + 1 ~ a[i] + d - 1
            dp[i] = min(dp[i], seg.query(a[i], a[i]) + i - 1);

            // a[i] + d + 1 ~ 1e6
            if (a[i] + 2 <= a.back())
                dp[i] = min(dp[i], seg.query(a[i] + 2, a.back()) + i - 1);

            if (dp[i] - i < seg.query(a[i], a[i])) {
                seg.update(a[i], dp[i] - i);
            }
        }
        int cur_ans = INT_MAX;
        for (int i = 0; i < a.size(); i++) {
            cur_ans = min(cur_ans, dp[i] + (int)(a.size()) - 1 - i);
        }
        ans += cur_ans;
    }

    cout << ans << '\n';

    return 0;
}