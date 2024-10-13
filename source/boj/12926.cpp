// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// pbs
vector<ll> solve(ll n, ll x0, ll a, ll b, vector<ll> &v)
{
    ll q = v.size();
    vector<ll> ans(q, -1);
    vector<ll> l(q, 0), r(q, MOD1 - 1);

    while (true) {
        bool flag = false;
        vector<ll> m(q);
        // cnt[i]: the count of number
        // which are leq than m[i]
        // among x0, x1, x2, ..., xn-1

        vector<int> mid_vals;
        for (int i = 0; i < q; i++) {
            if (l[i] == r[i]) {
                ans[i] = l[i];
                continue;
            }
            m[i] = (l[i] + r[i]) / 2;
            mid_vals.push_back(m[i]);
            flag = true;
        }

        if (!flag) {
            break;
        }

        sort(mid_vals.begin(), mid_vals.end());
        mid_vals.erase(unique(mid_vals.begin(), mid_vals.end()), mid_vals.end());
        vector<int> cnt(mid_vals.size());

        vector<vector<int>> mid_vals_idx(mid_vals.size());
        for (int i = 0; i < q; i++) {
            if (ans[i] != -1) {
                continue;
            }
            int idx = lower_bound(mid_vals.begin(), mid_vals.end(), m[i]) - mid_vals.begin();
            mid_vals_idx[idx].push_back(i);
        }

        ll x = x0;
        for (int i = 0; i < n; i++) {
            // can be optimized with binary search and prefix sum
            // for (int j = 0; j < mid_vals.size(); j++) {
            //     if (x <= mid_vals[j]) {
            //         cnt[j]++;
            //     }
            // }
            int idx = lower_bound(mid_vals.begin(), mid_vals.end(), x) - mid_vals.begin();
            if (idx != mid_vals.size()) {
                cnt[idx]++;
            }
            x = (x * a + b) % MOD1;
        }

        for (int i = 1; i < mid_vals.size(); i++) {
            cnt[i] += cnt[i - 1];
        }

        for (int i = 0; i < mid_vals.size(); i++) {
            for (int j : mid_vals_idx[i]) {
                if (cnt[i] > v[j]) {
                    r[j] = m[j];
                }
                else {
                    l[j] = m[j] + 1;
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, x0, a, b;
    cin >> n >> x0 >> a >> b;
    ll q;
    cin >> q;
    vector<ll> v(q);
    for (ll i = 0; i < q; i++) {
        cin >> v[i];
    }

    vector<ll> ans = solve(n, x0, a, b, v);
    ll ans_sum = accumulate(ans.begin(), ans.end(), 0LL);
    cout << ans_sum << endl;

    return 0;
}