#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        int m;
        cin >> m;
        vector<ll> dp(m + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = v[i]; j <= m; j++) {
                dp[j] += dp[j - v[i]];
            }
        }

        cout << dp[m] << '\n';
    }

    return 0;
}