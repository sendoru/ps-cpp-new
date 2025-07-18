// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll INV_2 = (MOD1 + 1) / 2;

struct SegTree {
    vector<ll> tree;
    int size;

    SegTree(int n) {
        size = 1;
        while (size < n) {
            size <<= 1;
        }
        tree.assign(2 * size, 0);
    }
    void update(int idx, ll val) {
        idx += size;
        tree[idx] = val % MOD1;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = (tree[2 * idx] + tree[2 * idx + 1]) % MOD1;
        }
    }
    ll query(int l, int r) {
        ll res = 0;
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) {
                res += tree[l++];
                res %= MOD1;
            }
            if (r & 1) {
                res += tree[--r];
                res %= MOD1;
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    ll query(int idx) {
        return tree[idx + size];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m;
    cin >> m;
    vector<ll> k(m), n(m);
    vector<vector<int>> b(m);
    vector<int> b_unique;
    for (int i = 0; i < m; i++) {
        cin >> k[i] >> n[i];
        b[i].resize(n[i]);
        for (int j = 0; j < n[i]; j++) {
            cin >> b[i][j];
        }
        b_unique.insert(b_unique.end(), b[i].begin(), b[i].end());
    }
    sort(b_unique.begin(), b_unique.end());
    b_unique.erase(unique(b_unique.begin(), b_unique.end()), b_unique.end());
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n[i]; j++) {
            b[i][j] = lower_bound(b_unique.begin(), b_unique.end(), b[i][j]) - b_unique.begin();
        }
    }

    ll ans = 0;
    SegTree seg1(b_unique.size()), seg2(b_unique.size());
    ll b_u_size = b_unique.size();
    for (int i = 0; i < m; i++) {
        // 1. 앞에 있는 것들이랑 b[i] 비교
        for (int j = 0; j < n[i]; j++) {
            int idx = b[i][j];
            ans += seg1.query(idx + 1, b_u_size) * k[i];
            ans %= MOD1;
        }
        // 2. b[i] 내부에서 비교
        // 2-1. j0 < j1이고 b[i][j0] > b[i][j1]인 경우 추가 처리
        for (int j = 0; j < n[i]; j++) {
            int idx = b[i][j];
            ans += seg2.query(idx + 1, b_u_size) * k[i];
            ans %= MOD1;
            seg2.update(idx, seg2.query(idx) + 1);
        }
        // 2-2. 2-1을 포함한 모든 경우
        for (int j = 0; j < n[i]; j++) {
            int idx = b[i][j];
            ans += seg2.query(idx + 1, b_u_size) * k[i] % MOD1 * (k[i] - 1) % MOD1 * INV_2 % MOD1;
            ans %= MOD1;
        }
        // 3. seg1 업데이트
        for (int j = 0; j < n[i]; j++) {
            int idx = b[i][j];
            seg1.update(idx, seg1.query(idx) + k[i]);
        }
        // 4. seg2 초기화
        for (int j = 0; j < n[i]; j++) {
            int idx = b[i][j];
            seg2.update(idx, 0);
        }
    }

    cout << ans;

    return 0;
}