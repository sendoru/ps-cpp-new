// #include "atcoder/all"
#pragma GCC optimize("O3")
// fast float

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#pragma GCC target("avx2")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const int X_SCALE = 18;
const int Y_SCALE = 360;
const int DP_LOOKUP = 36;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        ll n;
        double a, b;
        cin >> n >> a >> b;
        vector<double> islands(n);
        for (int i = 0; i < n; i++) {
            cin >> islands[i];
        }

        vector<double> vals;
        vals.push_back(a);
        vals.push_back(b);
        for (int i = 0; i < n; i++) {
            vals.push_back(islands[i]);
        }
        sort(vals.begin(), vals.end());
        double offset = (vals[0] + vals.back()) / 2;
        a -= offset;
        b -= offset;
        for (int i = 0; i < n; i++) {
            islands[i] -= offset;
        }

        vector<vector<double>> dp(2 * 10 * X_SCALE + 1, vector<double>(3 * 10 * Y_SCALE + 1, MOD9));

        dp[0][(ll)((a + 15) * Y_SCALE)] = 0;

        for (int i = 1; i < dp.size(); i++) {
            double x = (double)i / X_SCALE - 10;
            for (int j = 0; j < dp[i].size(); j++) {
                double y = (double)j / Y_SCALE - 15;
                for (int k = max(0, j - DP_LOOKUP); k <= min((int)dp[i].size() - 1, j + DP_LOOKUP); k++) {
                    double x_pre = (double)(i - 1) / X_SCALE - 10;
                    double y_pre = (double)k / Y_SCALE - 15;
                    double path_len = sqrt(double(k - j) * (k - j) / Y_SCALE / Y_SCALE + (double)1 / X_SCALE / X_SCALE);
                    double rad = 0;
                    for (int l = 0; l < islands.size(); l++) {
                        // double island_dist_sq_1 = x * x + (y - islands[l]) * (y - islands[l]);
                        // double island_dist_sq_2 = x_mid * x_mid + (y_mid - islands[l]) * (y_mid - islands[l]);
                        // double island_dist_sq_3 = (x + (double)1 / X_SCALE) * (x + (double)1 / X_SCALE) + (y_pre - islands[l]) * (y_pre - islands[l]);
                        // if (island_dist_sq_1 < 1e-12 || island_dist_sq_2 <= 1e-12 || island_dist_sq_3 <= 1e-12) {
                        //     rad = MOD9;
                        // } else {
                        //     rad += 0.25 / island_dist_sq_1 + 0.5 / island_dist_sq_2 + 0.25 / island_dist_sq_3;
                        // }
                        double island_dist_sq_1 = x * x + (y - islands[l]) * (y - islands[l]);
                        double island_dist_sq_2 = x_pre * x_pre + (y_pre - islands[l]) * (y_pre - islands[l]);
                        if (island_dist_sq_1 <= 1e-12 || island_dist_sq_2 <= 1e-12) {
                            rad = MOD9;
                        } else {
                            rad += .5 / island_dist_sq_1 + .5 / island_dist_sq_2;
                        }
                    }
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + path_len * (1 + rad));
                }
            }
        }

        cout << "Case #" << t << ": " << dp.back()[(ll)((b + 15) * Y_SCALE)] << endl;
    }

    return 0;
}