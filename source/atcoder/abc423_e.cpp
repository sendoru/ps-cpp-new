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

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pf_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        pf_sum[i] = pf_sum[i - 1] + a[i];
    }
    vector<ll> lt_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        lt_sum[i] = lt_sum[i - 1] + pf_sum[i];
    }
    vector<ll> ut_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        ut_sum[i] = ut_sum[i - 1] + a[i] * i;
    }
    vector<ll> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + ut_sum[i];
    }

    while (q--) {
        ll l, r;
        cin >> l >> r;
        ll ans = dp[r];
        ans -= ut_sum[l - 1] * (r - l + 1);
        ans -= dp[l - 1];
        ans -= (l - 1) * (lt_sum[r] - lt_sum[l - 1] - (r - l + 1) * pf_sum[l - 1]);
        cout << ans << '\n';
    }

    return 0;
}