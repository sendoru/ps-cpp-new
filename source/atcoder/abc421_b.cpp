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

    ll x, y;
    cin >> x >> y;
    vector<ll> dp(10);
    dp[0] = x;
    dp[1] = y;
    for (int i = 2; i < 10; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
        string tmp = to_string(dp[i]);
        reverse(tmp.begin(), tmp.end());
        dp[i] = stoll(tmp);
    }

    cout << dp[9] << "\n";

    return 0;
}