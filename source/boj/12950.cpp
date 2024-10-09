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

    int n, m;
    cin >> n >> m;
    vector<vector<char>> adj_mat(n, vector<char>(n));
    for (int i = 0; i < m; i++) {
        int s, e;
        char c;
        cin >> s >> e >> c;
        adj_mat[s][e] = c;
        adj_mat[e][s] = c;
    }

    // shortest palindromic walk 0 -> 1
    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dp[i][j] = 0;
            }
            else if (adj_mat[i][j] != 0) {
                dp[i][j] = 1;
            }
        }
    }

    vector<vector<int>> visited(n, vector<int>(n));

    function<int(int, int, int)> solve = [&](int s, int e, int visited_limit) {
        if (dp[s][e] != -1) {
            return dp[s][e];
        }

        int &ret = dp[s][e];
        ret = 1e9;

        for (int i = 0; i < n; i++) {
            if (i == s || i == e) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (j == s || j == e) {
                    continue;
                }
                if (adj_mat[s][i] != 0 && adj_mat[j][e] != 0 && adj_mat[s][i] == adj_mat[j][e] && visited[i][j] < visited_limit) {
                    visited[i][j]++;
                    ret = min(ret, solve(i, j, visited_limit) + 2);
                }
            }
        }

        return ret;
    };

    int ans = 1e9;

    for (int i = 1; i <= 20; i++) {
        ans = min(ans, solve(0, 1, i));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = -1;
                if (i == j) {
                    dp[i][j] = 0;
                }
                else if (adj_mat[i][j] != 0) {
                    dp[i][j] = 1;
                }
            }
        }
        visited = vector<vector<int>>(n, vector<int>(n));
    }
    cout << (ans >= 1e9 ? -1 : ans) << '\n';

    return 0;
}