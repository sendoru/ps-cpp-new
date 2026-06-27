// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        string s;
        cin >> s;
        vector<ll> x(n), y(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        for (int i = 1; i < n; i++) {
            cin >> y[i];
        }

        vector<array<ll, 2>> dp(n);
        if (s[0] == 'S') {
            dp[0] = {0, -x[0]};
        }
        else {
            dp[0] = {-x[0], 0};
        }
        for (int i = 1; i < n; i++) {
            if (s[i] == 'S') {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + y[i]);
                dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) - x[i];
            }
            else {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + y[i]) - x[i];
                dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);
            }
        }

        cout << max(dp[n - 1][0], dp[n - 1][1]) << '\n';
    }

    return 0;
}