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
    vector<ll> tree;
    ll sz;
    SegTree(ll n) {
        sz = 1;
        while(sz < n) {
            sz <<= 1;
        }
        tree.assign(2 * sz, 0);
    }
    void update(int idx, ll val) {
        idx += sz;
        tree[idx] = val;
        while(idx > 1) {
            idx >>= 1;
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }
    ll query(int l, int r) {
        l += sz;
        r += sz;
        ll res = 0;
        while(l < r) {
            if (l % 2 == 1) {
                res += tree[l];
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res += tree[r];
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> p(n);
    for (ll i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    if (n == 1 || n == 2) {
        cout << 0;
        return 0;
    }

    SegTree seg1(n), seg2(n);
    vector<ll> dp1(n), dp2(n);

    // dp1[i]: number of len-2 increasing subseq ending with p[i] (=inversion count)
    seg1.update(p[0], 1);
    for (int i = 1; i < n; i++) {
        ll val = (seg1.query(0, p[i])) % MOD9;
        dp1[i] = val;
        seg1.update(p[i], 1);
    }

    // dp2[i]: number of len-2 decreasing subseq starting with p[i]
    seg2.update(p.back(), 1);
    for (int i = n - 2; i >= 0; i--) {
        ll val = (seg2.query(0, p[i])) % MOD9;
        dp2[i] = val;
        seg2.update(p[i], 1);
    }

    vector<ll> dp2_fix(n);
    vector<ll> pow2(n + 1), pow2_inv(n + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD9;
    }
    pow2_inv[0] = 1;
    ll inv2 = (MOD9 + 1) / 2;
    for (int i = 1; i <= n; i++) {
        pow2_inv[i] = (pow2_inv[i - 1] * inv2) % MOD9;
    }
    for (int i = 0; i < n; i++) {
        dp2_fix[i] = (dp2[i] * pow2[i]) % MOD9 * inv2 % MOD9;
    }
    vector<ll> pf_sum(n + 1);
    for (int i = 0; i < n; i++) {
        pf_sum[i + 1] = (pf_sum[i] + dp2_fix[i]) % MOD9;
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dp1[i] * pow2_inv[i] % MOD9 * (pf_sum.back() + MOD9 - pf_sum[i + 1] + dp2[i] * pow2[i] % MOD9) % MOD9;
        ans %= MOD9;
    }

    cout << ans;
    return 0;
}