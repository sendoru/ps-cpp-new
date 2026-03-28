// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct RangeUpdatePointQuery2D {
    // assuming it is square
    int n;
    vector<vector<int>> data;
    RangeUpdatePointQuery2D(int _n) {
        n = 1;
        while (n < _n)
            n <<= 1;
        data.assign(n * 2, vector<int>(n * 2, 0));
    }

    void update_inner(int node_r, int c1, int c2, int val) {
        int l = c1 + n, r = c2 + n + 1;
        while (l < r) {
            if (l & 1) {
                data[node_r][l] = max(data[node_r][l], val);
                l++;
            }
            if (r & 1) {
                r--;
                data[node_r][r] = max(data[node_r][r], val);
            }
            l >>= 1;
            r >>= 1;
        }
    }

    void update(int r1, int c1, int r2, int c2, int val) {
        int l = r1 + n, r = r2 + n + 1;
        while (l < r) {
            if (l & 1) {
                update_inner(l, c1, c2, val);
                l++;
            }
            if (r & 1) {
                r--;
                update_inner(r, c1, c2, val);
            }
            l >>= 1;
            r >>= 1;
        }
    }

    int query(int r, int c) {
        int res = 0;
        for (int i = r + n; i > 0; i >>= 1) {
            int idx = c + n;
            while (idx > 0) {
                res = max(res, data[i][idx]);
                idx >>= 1;
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        grid.push_back(s);
    }

    vector<vector<int>> pf_sum(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pf_sum[i + 1][j + 1] = pf_sum[i + 1][j] + pf_sum[i][j + 1] - pf_sum[i][j] + (grid[i][j] == '#' ? 1 : 0);
        }
    }

    RangeUpdatePointQuery2D seg(max(n, m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                continue;
            }
            int hi = min(n - i, m - j), lo = 1;
            int ans = 0;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                int sum = pf_sum[i + mid][j + mid] - pf_sum[i + mid][j] - pf_sum[i][j + mid] + pf_sum[i][j];
                if (sum == 0) {
                    ans = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            seg.update(i, j, i + ans - 1, j + ans - 1, ans);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int r, c;
        cin >> r >> c;
        r--;
        c--;
        int len = seg.query(r, c);
        cout << len * len << "\n";
    }

    return 0;
}