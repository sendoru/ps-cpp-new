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

    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> used(10);
    for (int i = 0; i < n; i++) {
        int digit;
        cin >> digit;
        used[digit] = true;
    }

    vector<ll> dp(k);
    for (int i = 1; i < 10; i++) {
        if (used[i]) {
            dp[i % k]++;
        }
    }

    for (int i = 2; i <= m; i++) {
        vector<ll> ndp(k);
        for (int j = 0; j < k; j++) {
            for (int d = 0; d < 10; d++) {
                if (used[d]) {
                    ndp[(j * 10 + d) % k] += dp[j];
                    ndp[(j * 10 + d) % k] %= MOD1;
                }
            }
        }
        dp = ndp;
    }

    cout << dp[0];

    return 0;
}