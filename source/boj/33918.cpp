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

    int n, m, c, d;
    cin >> n >> m >> c >> d;
    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<vector<ll>> dp(n, vector<ll>(m + 1, -1e18));
    for (int i = 1; i <= m; i++) {
        dp[0][i] = m - abs(b[0] - i);
    }
    vector<deque<pll>> deques(c);
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m + 2 * d; j++) {
            int mod = j % c;
            while (!deques[mod].empty() && deques[mod].front().first < j - 2 * d) {
                deques[mod].pop_front();
            }
            if (j <= m) {
                while (!deques[mod].empty() && deques[mod].back().second <= dp[i - 1][j]) {
                    deques[mod].pop_back();
                }
                deques[mod].emplace_back(j, dp[i - 1][j]);
            }
            if (!deques[mod].empty() && j - d > 0 && j - d <= m) {
                dp[i][j - d] = max(dp[i][j - d], deques[mod].front().second + m - abs(b[i] - (j - d)));
            }
        }
        for (int j = 0; j < c; j++) {
            deques[j].clear();
        }
    }

    cout << *max_element(dp[n - 1].begin(), dp[n - 1].end());

    return 0;
}