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
        while (n < size) {
            n <<= 1;
        }
        tree.assign(2 * n, 0);
    }

    void update(int idx, ll val) {
        idx += n;
        tree[idx] = val;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }

    // Query the sum in the range [l, r)
    ll query(int l, int r) {
        l += n;
        r += n;
        ll sum = 0;
        while (l < r) {
            if (l & 1) {
                sum += tree[l];
                l++;
            }
            if (r & 1) {
                r--;
                sum += tree[r];
            }
            l >>= 1;
            r >>= 1;
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> abc(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> abc[i][0] >> abc[i][1] >> abc[i][2];
    }

    vector<vector<pii>> by_b(50001);
    for (int i = 0; i < n; i++) {
        int a = abc[i][0], b = abc[i][1], c = abc[i][2];
        by_b[b].emplace_back(a, c);
    }

    ll ans = 0;
    SegTree st(50001);
    for (int b = 0; b < 50001; b++) {
        for (auto &[a, c] : by_b[b]) {
            if (st.query(a, b + 1) >= c) {
                continue;
            }
            int idx = b;
            // ll need = c - st.query(a, b + 1);
            vector<int> to_erase;
            for (ll need = c - st.query(a, b + 1); need > 0; idx--) {
                if (st.query(idx, idx + 1) == 0) {
                    st.update(idx, 1);
                    ans++;
                    need--;
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}