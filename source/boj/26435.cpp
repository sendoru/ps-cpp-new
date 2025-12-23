// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct MaxSegTree {
    vector<ll> tree;
    int n;
    MaxSegTree(int size) {
        n = 1;
        while (n < size) {
            n <<= 1;
        }
        tree.resize(2 * n, -1e15);
    }
    void update(int idx, ll val) {
        idx += n;
        tree[idx] = max(tree[idx], val);
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
        }
    }
    ll query(int l, int r) {
        ll res = -1e15;
        l += n;
        r += n;
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
};

ll solve() {
    ll n, e;
    cin >> n >> e;
    vector<array<ll, 3>> xyc(n);
    for (int i = 0; i < n; i++) {
        cin >> xyc[i][0] >> xyc[i][1] >> xyc[i][2];
    }
    sort(xyc.begin(), xyc.end(), [](const array<ll, 3>& a, const array<ll, 3>& b) {
        return a[1] < b[1];
    });
    vector<vector<array<ll, 2>>> xc_by_y;
    ll prev_y = -1e15;
    for (int i = 0; i < n; i++) {
        ll x = xyc[i][0];
        ll y = xyc[i][1];
        ll c = xyc[i][2];
        if (y != prev_y) {
            xc_by_y.push_back({});
            prev_y = y;
        }
        xc_by_y.back().push_back({x, c});
    }
    reverse(xc_by_y.begin(), xc_by_y.end());
    for (auto& vec : xc_by_y) {
        sort(vec.begin(), vec.end());
    }
    MaxSegTree left_seg(1e5 + 10), right_seg(1e5 + 10);
    right_seg.update(0, 0);
    left_seg.update(0, -e);
    ll ans = 0;
    for (auto & vec : xc_by_y) {
        vector<ll> left_dp(vec.size(), -1e15), right_dp(vec.size(), -1e15);
        // 1. 왼쪽 -> 오른쪽 방향전환
        right_dp[0] = left_seg.query(0, left_seg.n) + vec[0][1] - e;
        for (int i = 1; i < vec.size(); i++) {
            right_dp[i] = right_dp[i - 1] + vec[i][1];
        }
        // 2. 오른쪽 -> 왼쪽 방향전환
        left_dp.back() = right_seg.query(0, right_seg.n) + vec.back()[1] - e;
        for (int i = (int)vec.size() - 2; i >= 0; i--) {
            left_dp[i] = left_dp[i + 1] + vec[i][1];
        }
        // 3. 오른쪽 정방향 유지
        for (int i = 0; i < vec.size(); i++) {
            ll query_val = right_seg.query(0, vec[i][0] + 1);
            right_seg.update(vec[i][0], query_val + vec[i][1]);
        }
        // 4. 왼쪽 정방향 유지
        for (int i = (int)vec.size() - 1; i >= 0; i--) {
            ll query_val = left_seg.query(vec[i][0], left_seg.n);
            left_seg.update(vec[i][0], query_val + vec[i][1]);
        }
        for (int i = 0; i < right_dp.size(); i++) {
            right_seg.update(vec[i][0], right_dp[i]);
            left_seg.update(vec[i][0], left_dp[i]);
        }
        ans = max(ans, right_seg.query(0, right_seg.n));
        ans = max(ans, left_seg.query(0, left_seg.n));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": " << solve() << "\n";
    }

    return 0;
}