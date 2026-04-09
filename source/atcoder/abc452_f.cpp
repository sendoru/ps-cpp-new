#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll add(ll a, ll b) {
    return a + b;
}

ll e() {
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<ll> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    atcoder::segtree<ll, add, e> seg(n + 10);
    ll ans = 0, cur_inv = 0, pre_lower_bound = -1;
    for (ll l = 0, r = 0; l < n; l++) {
        ll lower_bound = -1;
        if (l != 0) {
            cur_inv -= seg.prod(0, p[l - 1]);
            seg.set(p[l - 1], 0);
            if (cur_inv >= k) {
                lower_bound = pre_lower_bound;
            }
        }
        while (r < n && cur_inv + seg.prod(p[r] + 1, n) <= k) {
            cur_inv += seg.prod(p[r] + 1, n);
            seg.set(p[r], 1);
            if (lower_bound == -1 && cur_inv >= k) {
                lower_bound = r;
            }
            r++;
        }
        if (lower_bound == -1) {
            lower_bound = r;
        }
        ans += r - lower_bound;
        pre_lower_bound = lower_bound;
    }

    // if (k == 0) {
    //     ans -= n;
    // }

    cout << ans;

    return 0;
}