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

    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<int>> dp(n, vector<int>(n, -1));
    vector<pii> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    function<int(int, int)> dfs = [&](int x, int y) {
        if (dp[x][y] != -1) {
            return dp[x][y];
        }
        int &res = dp[x][y];
        res = 1;
        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                continue;
            }
            if (grid[nx][ny] > grid[x][y]) {
                res = max(res, dfs(nx, ny) + 1);
            }
        }
        return res;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = max(ans, dfs(i, j));
        }
    }

    cout << ans;

    return 0;
}