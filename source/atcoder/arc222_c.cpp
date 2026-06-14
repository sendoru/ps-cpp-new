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
        vector<vector<ll>> grid(n, vector<ll>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        vector<vector<ll>> dp_down(n, vector<ll>(n, -1));
        auto dp_up = dp_down;

        // down
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0) {
                    if (j == 0) {
                        dp_down[i][j] = grid[i][j + 1];
                    } else if (j == n - 1) {
                        dp_down[i][j] = grid[i][j - 1];
                    } else {
                        dp_down[i][j] = grid[i][j - 1] + grid[i][j + 1];
                    }
                } else {
                    if (j == 0) {
                        dp_down[i][j] = grid[i][j + 1] + dp_down[i - 1][j + 1];
                    } else if (j == n - 1) {
                        dp_down[i][j] = grid[i][j - 1] + dp_down[i - 1][j - 1];
                    } else {
                        dp_down[i][j] = grid[i][j - 1] + grid[i][j + 1] + min(dp_down[i - 1][j - 1], dp_down[i - 1][j + 1]);
                    }
                }
            }
        }

        // up
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                if (i == n - 1) {
                    if (j == 0) {
                        dp_up[i][j] = grid[i][j + 1];
                    } else if (j == n - 1) {
                        dp_up[i][j] = grid[i][j - 1];
                    } else {
                        dp_up[i][j] = grid[i][j - 1] + grid[i][j + 1];
                    }
                } else {
                    if (j == 0) {
                        dp_up[i][j] = grid[i][j + 1] + dp_up[i + 1][j + 1];
                    } else if (j == n - 1) {
                        dp_up[i][j] = grid[i][j - 1] + dp_up[i + 1][j - 1];
                    } else {
                        dp_up[i][j] = grid[i][j - 1] + grid[i][j + 1] + min(dp_up[i + 1][j - 1], dp_up[i + 1][j + 1]);
                    }
                }
            }
        }

        vector<vector<ll>> ans(n, vector<ll>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ll left = 1e18, right = 1e18;
                if (j != 0) {
                    left = dp_down[i][j - 1] + dp_up[i][j - 1] - grid[i][j];
                    if (j != 1) {
                        left -= grid[i][j - 2];
                    }
                }
                if (j != n - 1) {
                    right = dp_down[i][j + 1] + dp_up[i][j + 1] - grid[i][j];
                    if (j != n - 2) {
                        right -= grid[i][j + 2];
                    }
                }
                ans[i][j] = min(left, right);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << ans[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}