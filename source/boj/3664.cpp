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

    int t;
    cin >> t;
    while (t--) {
        double a, b, v_max, f;
        cin >> a >> b >> v_max >> f;

        int r;
        cin >> r;
        vector<double> dist(r), slope(r);
        for (int i = 0; i < r; i++) {
            double x, y;
            cin >> x >> y;
            dist[i] = sqrt(x * x + y * y) / 1000.0;
            slope[i] = y / x;
        }

        for (int i = 0; i < r; i++) {
            if (slope[i] > 0) {
                f -= dist[i] * slope[i] * b;
            }
        }
        if (f < 0) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        double lo = 0.00001, hi = v_max;
        double v_opt = lo;
        for (int _ = 0; _ < 100; _++) {
            double v_mid = (lo + hi) / 2.0;
            double cost = 0;
            for (int i = 0; i < r; i++) {
                if (slope[i] >= 0) {
                    cost += dist[i] * a * v_mid;
                } else {
                    cost += dist[i] * max(0.0, a * v_mid + slope[i] * b);
                }
            }
            if (cost <= f) {
                v_opt = max(v_opt, v_mid);
                lo = v_mid;
            } else {
                hi = v_mid;
            }
        }

        double ans = 0;
        for (int i = 0; i < r; i++) {
            if (-b * slope[i] / a > v_opt) {
                if (-b * slope[i] / a > v_max) {
                    ans += dist[i] / v_max;
                } else {
                    ans += dist[i] / (-b * slope[i] / a);
                }
            } else {
                ans += dist[i] / v_opt;
            }
        }

        cout << fixed << setprecision(10) << ans << '\n';
    }

    return 0;
}