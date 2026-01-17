// #include "atcoder/all"
#pragma GCC optimize("Ofast")
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
    vector<ll> p(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> v[i];
    }

    // knapsack with backtracking
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, -1));
    vector<vector<array<int, 2>>> last_chosen(n + 1, vector<array<int, 2>>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // not choose
            // if last_chosen[i][j] contains -1,
            // follow previous dp[i - 1][j] when reconstructing answer
            dp[i][j] = dp[i - 1][j];
            last_chosen[i][j] = {-1, -2};
            // choose
            if (j >= p[i - 1]) {
                if (dp[i - 1][j - p[i - 1]] + v[i - 1] > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j - p[i - 1]] + v[i - 1];
                    last_chosen[i][j] = {i - 1, -2};
                } else if (dp[i - 1][j - p[i - 1]] + v[i - 1] == dp[i][j]) {
                    last_chosen[i][j] = {-1, i - 1};
                }
            }
        }
    }

    ll opt = *max_element(dp[n].begin(), dp[n].end());
    vector<bool> cur(m + 1);
    // 0: must be selected
    // 1: may be selected
    // 2: must not be selected
    vector<int> ans(n, 1);
    for (int j = 0; j <= m; j++) {
        if (dp[n][j] == opt) {
            cur[j] = true;
        }
    }

    for (int i = n; i >= 1; i--) {
        vector<bool> next(m + 1, false);
        int chosens = 0;
        for (int j = 0; j <= m; j++) {
            if (!cur[j]) {
                continue;
            }
            for (ll chosen : last_chosen[i][j]) {
                if (chosen == -2) {
                    continue;
                }
                if (chosen == -1) {
                    // not chosen
                    chosens |= 2;
                    next[j] = true;
                } else {
                    // chosen
                    chosens |= 1;
                    next[j - p[chosen]] = true;
                }
            }
        }
        if (chosens == 1) {
            // must be selected
            ans[i - 1] = 0;
        } else if (chosens == 2) {
            // must not be selected
            ans[i - 1] = 2;
        }
        cur = next;
    }

    for (int i = 0; i < n; i++) {
        cout << (char)('A' + (char)ans[i]);
    }

    return 0;
}