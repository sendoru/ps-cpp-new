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

    int n, q;
    cin >> n >> q;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> new_grid(n, vector<int>(n, 0));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (grid[i][j] == '.' && grid[i - 1][j] == '.' && grid[i][j - 1] == '.' && grid[i - 1][j - 1] == '.') {
                new_grid[i][j] = 1;
            }
        }
    }

    vector<vector<int>> prefix_sum(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1] + new_grid[i][j];
        }
    }

    while (q--) {
        int r1, r2, c1, c2;
        cin >> r1 >> r2 >> c1 >> c2;
        r1--;
        r2--;
        c1--;
        c2--;
        int ans = prefix_sum[r2][c2] - prefix_sum[r1][c2] - prefix_sum[r2][c1] + prefix_sum[r1][c1];
        cout << ans << "\n";
    }

    return 0;
}