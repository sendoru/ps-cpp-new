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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> a(3, vector<int>(n));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
                a[i][j]--;
            }
        }

        vector<vector<int>> a_pos(3, vector<int>(n));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                a_pos[i][a[i][j]] = j;
            }
        }

        vector<vector<int>> dp(3, vector<int>(1 << n, -1));
        function<int(int, int)> dfs = [&](int turn, int mask) {
            if (dp[turn][mask] != -1) {
                return dp[turn][mask];
            }
            if (__builtin_popcount(mask) == 1) {
                for (int i = 0; i < n; i++) {
                    if ((mask >> i) & 1) {
                        return dp[turn][mask] = i;
                    }
                }
            }

            int n_turn = (turn + 1) % 3;
            int res = -1;
            // minimize a_pos[turn][res]
            int min_pos = n + 1;
            for (int pop = 0; pop < n; pop++) {
                if (!((mask >> pop) & 1)) {
                    continue;
                }
                int n_mask = mask ^ (1 << pop);
                int n_res = dfs(n_turn, n_mask);
                if (a_pos[turn][n_res] < min_pos) {
                    min_pos = a_pos[turn][n_res];
                    res = n_res;
                }
            }
            return dp[turn][mask] = res;
        };

        int mask = (1 << n) - 1;
        int res = dfs(0, mask);
        cout << res + 1 << "\n";
    }

    return 0;
}