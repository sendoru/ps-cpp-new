// #include "atcoder/all"
#pragma GCC optimize("O3")
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

    ll n, k, x;
    cin >> n >> k >> x;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    // sum(a) <= 16000
    vector<vector<int>> dp(k + 1, vector<int>(16001, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = k; j >= 1; j--) {
            for (int l = 16000; l >= a[i]; l--) {
                dp[j][l] |= dp[j - 1][l - a[i]];
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= 16000; i++) {
        if (dp[k][i]) {
            ans = max(ans, (ll)i * (k * x - i));
        }
    }

    cout << ans;

    return 0;
}