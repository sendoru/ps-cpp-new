// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MOD = 1000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    vector<array<ll, 2>> dp(n);
    if (s[0] != '0') {
        dp[0][0] = 1;
    }
    for (int i = 1; i < n; i++) {
        if (s[i] != '0') {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % MOD;
        }
        int num = (s[i - 1] - '0') * 10 + (s[i] - '0');
        if (num >= 10 && num <= 26) {
            if (i == 1) {
                dp[i][1] = 1;
            } else {
                dp[i][1] = (dp[i - 2][0] + dp[i - 2][1]) % MOD;
            }
        }
    }

    cout << (dp[n - 1][0] + dp[n - 1][1]) % MOD << "\n";

    return 0;
}