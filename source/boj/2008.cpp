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

    int n, m;
    cin >> n >> m;
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    int x, y;
    cin >> x >> y;

    vector<int> edges(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> edges[i];
        edges[i]--;
    }

    vector<vector<int>> dp(m + 1, vector<int>(n, MOD1));
    dp[0][a] = 0;
    for (int i = 1; i <= m; i++) {
        // prev column
        for (int j = 0; j < n; j++) {
            // current column
            for (int k = 0; k < n; k++) {
                if (k == edges[i]) {
                    dp[i][k + 1] = min(dp[i][k + 1], dp[i - 1][j] + abs(j - k) * y);
                    dp[i][k] = min(dp[i][k], dp[i - 1][j] + abs(j - k) * y + x);
                } else if (k == edges[i] + 1) {
                    dp[i][k - 1] = min(dp[i][k - 1], dp[i - 1][j] + abs(j - k) * y);
                    dp[i][k] = min(dp[i][k], dp[i - 1][j] + abs(j - k) * y + x);
                } else {
                    dp[i][k] = min(dp[i][k], dp[i - 1][j] + abs(j - k) * y);
                }
            }
        }
    }

    int answer = MOD1;
    for (int i = 0; i < n; i++) {
        answer = min(answer, dp[m][i] + abs(i - b) * y);
    }
    cout << answer << '\n';

    return 0;
}