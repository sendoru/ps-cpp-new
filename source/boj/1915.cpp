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
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> dp_left(n, vector<int>(m));
    auto dp_up = dp_left;
    auto dp_square = dp_left;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '0') {
                continue;
            }
            dp_left[i][j] = (j > 0 ? dp_left[i][j - 1] : 0) + 1;
            dp_up[i][j] = (i > 0 ? dp_up[i - 1][j] : 0) + 1;
            dp_square[i][j] = min({dp_left[i][j], dp_up[i][j], (i > 0 && j > 0 ? dp_square[i - 1][j - 1] : 0) + 1});
            ans = max(ans, dp_square[i][j]);
        }
    }

    cout << ans * ans;

    return 0;
}