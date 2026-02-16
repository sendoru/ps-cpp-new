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

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<array<ll, 2>> dp(n);
    dp[0][0] = a[0];
    dp[0][1] = -1e15;

    for (int i = 1; i < n; i++) {
        dp[i][0] = max(a[i], dp[i - 1][0] + a[i]);
        dp[i][1] = max(a[i], dp[i - 1][1] + a[i]);
        if (i > 1) {
            dp[i][1] = max(dp[i][1], dp[i - 2][0] + a[i]);
        }
    }

    ll ans = -1e15;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dp[i][0]);
        ans = max(ans, dp[i][1]);
    }

    if (ans == 0) {
        ans = *max_element(a.begin(), a.end());
    }

    cout << ans;

    return 0;
}