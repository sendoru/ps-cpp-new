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
    vector<bool> banned(n);
    for (int i = 0; i < m; i++) {
        int idx;
        cin >> idx;
        idx--;
        banned[idx] = true;
    }

    vector<vector<int>> dp(n, vector<int>(555, 1e8));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        if (banned[i]) {
            continue;
        }
        for (int j = 0; j < 555; j++) {
            for (int nj = max(1, j - 1); nj <= j + 1; nj++) {
                if (nj >= 555) {
                    continue;
                }
                int ni = i + nj;
                if (ni >= n) {
                    continue;
                }
                dp[ni][nj] = min(dp[ni][nj], dp[i][j] + 1);
            }
        }
    }

    int ans = *min_element(dp[n - 1].begin(), dp[n - 1].end());
    if (ans == 1e8) {
        ans = -1;
    }
    cout << ans;

    return 0;
}