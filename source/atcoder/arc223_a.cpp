// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n, mw;
        cin >> n >> mw;
        vector<ll> w(n), v(n);
        for (int i = 0; i < n; i++) {
            cin >> w[i] >> v[i];
        }

        vector<ll> w_pf_sum(n);
        w_pf_sum[0] = w[0];
        for (int i = 1; i < n; i++) {
            w_pf_sum[i] = w_pf_sum[i - 1] + w[i];
        }

        vector<ll> v_pf_sum(n);
        v_pf_sum[0] = v[0];
        for (int i = 1; i < n; i++) {
            v_pf_sum[i] = v_pf_sum[i - 1] + v[i];
        }

        // w[i] is larger than sum of previous ones
        // since mw >= w[i], we can take all items with weight <= mw

        function<ll(int, ll)> dfs = [&](int idx_max, ll remain_w) -> ll {
            if (idx_max < 0 || remain_w <= 0) {
                return 0;
            }

            // if we can take all, don't need to go further branch
            if (w_pf_sum[idx_max] <= remain_w) {
                return v_pf_sum[idx_max];
            }

            // 1) take idx_max
            ll nxt_remain_w = remain_w - w[idx_max];
            ll nxt_idx_max = upper_bound(w.begin(), w.begin() + idx_max, nxt_remain_w) - w.begin() - 1;
            ll take_value = v[idx_max] + dfs(nxt_idx_max, nxt_remain_w);

            // 2) skip idx_max
            ll skip_value = dfs(idx_max - 1, remain_w);
            return max(take_value, skip_value);
        };

        ll total_value = dfs(n - 1, mw);

        cout << total_value << "\n";
    }

    return 0;
}