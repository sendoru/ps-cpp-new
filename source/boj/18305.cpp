#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(vector<ll> &v, vector<vector<ll>> &dp, int l, int r) {
    if (l == r) {
        return 0;
    }
    if (l + 1 == r) {
        return v[l] + v[r];
    }
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    ll ret = INT64_MAX;
    ll sum = 0;
    for (int i = l; i <= r; i++) {
        sum += v[i];
    }
    for (int m = l; m < r; m++) {
        ret = min(ret, solve(v, dp, l, m) + solve(v, dp, m + 1, r) + sum);
    }
    return dp[l][r] = ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<vector<ll>> dp(n, vector<ll>(n, -1));

    cout << solve(v, dp, 0, n - 1) << '\n';

    return 0;
}