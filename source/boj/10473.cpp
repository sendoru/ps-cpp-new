// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

double dist(pdd a, pdd b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pdd s, e;
    cin >> s.x >> s.y >> e.x >> e.y;
    int n;
    cin >> n;
    vector<pdd> canons(n);
    for (int i = 0; i < n; i++) {
        cin >> canons[i].x >> canons[i].y;
    }

    // 0 ~ n - 1: canons
    // n: start
    // n + 1: end
    vector<vector<double>> adj_mat(n + 2, vector<double>(n + 2, 1e9));
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < n + 2; j++) {
            if (i == j) {
                adj_mat[i][j] = 0;
            }

            else if (i == n) {
                adj_mat[i][j] = dist(s, j == n + 1 ? e : canons[j]) / 5;
            } else if (i == n + 1) {
                adj_mat[i][j] = dist(e, j == n ? s : canons[j]) / 5;
            } else {
                double d = dist(canons[i], j == n + 1 ? e : (j == n ? s : canons[j]));
                adj_mat[i][j] = min(d / 5, 2 + abs(d - 50) / 5);
            }
        }
    }

    for (int k = 0; k < n + 2; k++) {
        for (int i = 0; i < n + 2; i++) {
            for (int j = 0; j < n + 2; j++) {
                adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
            }
        }
    }

    cout << fixed << setprecision(10) << adj_mat[n][n + 1] << "\n";

    return 0;
}