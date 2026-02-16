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

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        int n = (int)s1.size(), m = (int)s2.size(), l = (int)s3.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        dp[0][0] = true;
        function<bool(int, int)> dfs = [&](int i, int j) -> bool {
            if (i == 0 && j == 0) {
                return true;
            }
            if (dp[i][j] != -1) {
                return dp[i][j];
            }

            bool res = false;
            if (i != 0 && s1[i - 1] == s3[i + j - 1]) {
                res |= dfs(i - 1, j);
            }
            if (j != 0 && s2[j - 1] == s3[i + j - 1]) {
                res |= dfs(i, j - 1);
            }
            return dp[i][j] = res;
        };

        cout << "Data set " << t << ": " << (dfs(n, m) ? "yes" : "no") << '\n';
    }

    return 0;
}