// #include "atcoder/all"
#pragma GCC optimize("O3,Ofast")
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
        int r, c;
        cin >> r >> c;
        vector<string> grid(r);
        for (int i = 0; i < r; i++) {
            cin >> grid[i];
        }

        vector<vector<int>> grid_int;
        if (r < c) {
            grid_int.resize(r, vector<int>(c, 0));
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    grid_int[i][j] = grid[i][j] == '.' ? -1 : 1;
                }
            }
        } else {
            grid_int.resize(c, vector<int>(r, 0));
            for (int i = 0; i < c; i++) {
                for (int j = 0; j < r; j++) {
                    grid_int[i][j] = grid[j][i] == '.' ? -1 : 1;
                }
            }
            swap(r, c);
        }

        ll ans = 0;
        for (int i = 0; i < r; i++) {
            vector<int> prefix_sum(c, 0);

            for (int j = i; j < r; j++) {
                prefix_sum[0] += grid_int[j][0];
                int cur = grid_int[j][0];
                for (int k = 1; k < c; k++) {
                    cur += grid_int[j][k];
                    prefix_sum[k] += cur;
                }

                vector<int> cnt(2 * c * (j - i + 1) + 1, 0);
                cnt[c * (j - i + 1)] = 1;
                for (int k = 0; k < c; k++) {
                    ans += cnt[prefix_sum[k] + c * (j - i + 1)];
                    cnt[prefix_sum[k] + c * (j - i + 1)]++;
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}