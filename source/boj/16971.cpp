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

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    ll bs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int eg = 0;
            if (i == 0 || i == n - 1) {
                eg++;
            }
            if (j == 0 || j == m - 1) {
                eg++;
            }

            if (eg == 2) {
                bs += a[i][j];
            } else if (eg == 1) {
                bs += a[i][j] * 2;
            } else {
                bs += a[i][j] * 4;
            }
        }
    }

    // swap row
    ll max_diff = 0;
    vector<ll> row_eg(n, 0), row_not_eg(n, 0);
    for (int i = 0; i < n; i++) {
        row_eg[i] += a[i][0] + a[i][m - 1];
        row_not_eg[i] += 2 * (a[i][0] + a[i][m - 1]);
        for (int j = 1; j < m - 1; j++) {
            row_eg[i] += 2 * a[i][j];
            row_not_eg[i] += 4 * a[i][j];
        }
    }

    for (int i = 1; i < n - 1; i++) {
        max_diff = max(max_diff, row_eg[i] + row_not_eg[0] - row_not_eg[i] - row_eg[0]);
        max_diff = max(max_diff, row_eg[i] + row_not_eg[n - 1] - row_not_eg[i] - row_eg[n - 1]);
    }

    // swap col
    vector<ll> col_eg(m, 0), col_not_eg(m, 0);
    for (int j = 0; j < m; j++) {
        col_eg[j] += a[0][j] + a[n - 1][j];
        col_not_eg[j] += 2 * (a[0][j] + a[n - 1][j]);
        for (int i = 1; i < n - 1; i++) {
            col_eg[j] += 2 * a[i][j];
            col_not_eg[j] += 4 * a[i][j];
        }
    }

    for (int j = 1; j < m - 1; j++) {
        max_diff = max(max_diff, col_eg[j] + col_not_eg[0] - col_not_eg[j] - col_eg[0]);
        max_diff = max(max_diff, col_eg[j] + col_not_eg[m - 1] - col_not_eg[j] - col_eg[m - 1]);
    }

    cout << bs + max_diff;

    return 0;
}