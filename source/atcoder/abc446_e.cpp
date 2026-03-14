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

    ll m, a, b;
    cin >> m >> a >> b;

    ll ans = 0;
    vector<vector<int>> dp(m, vector<int>(m, -1));
    set<array<int, 2>> stack;
    function<int(int, int)> solve = [&](int x, int y) {
        if (x == 0 || y == 0) {
            return 0;
        }
        if (dp[x][y] != -1) {
            stack.erase({x, y});
            return dp[x][y];
        }
        if (stack.count({x, y})) {
            stack.erase({x, y});
            return dp[x][y] = 1;
        }
        stack.insert({x, y});
        dp[x][y] = solve(y, (y * a + x * b) % m);
        stack.erase({x, y});
        return dp[x][y];
    };

    for (ll x = 1; x < m; x++) {
        for (ll y = 1; y < m; y++) {
            if (solve(x, y)) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}