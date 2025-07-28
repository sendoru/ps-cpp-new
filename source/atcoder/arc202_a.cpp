// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

map<pii, pll> dp;

pll solve(vector<ll> &a, ll l, ll r) {
    if (l == r) {
        return {0, a[l]};
    } else if (l + 1 == r) {
        return {abs(a[l] - a[r]), max(a[l], a[r]) + 1};
    }
    if (dp.count({l, r})) {
        return dp[{l, r}];
    }
    int mid = (l + r) / 2;
    ll min_diff = LLONG_MAX;
    ll max_val = 0;
    for (int i = mid - 20; i <= mid + 20; i++) {
        if (i < l || i >= r) {
            continue;
        }
        pll l_res = solve(a, l, i);
        pll r_res = solve(a, i + 1, r);
        ll diff = l_res.first + r_res.first + abs(l_res.second - r_res.second);
        if (diff < min_diff) {
            min_diff = diff;
            max_val = max(l_res.second, r_res.second) + 1;
        }
    }
    dp[{l, r}] = {min_diff, max_val};
    return dp[{l, r}];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        dp.clear();
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        solve(a, 0, n - 1);
        cout << dp[{0, n - 1}].first << "\n";
    }

    return 0;
}