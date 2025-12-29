// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// returns intersection point of infinite line a1a2 and b1b2 if it is unique, nullopt otherwise
optional<pdd> intersect(const pdd& a1, const pdd& a2, const pdd& b1, const pdd& b2) {
    double A1 = a2.second - a1.second;
    double B1 = a1.first - a2.first;
    double C1 = A1 * a1.first + B1 * a1.second;

    double A2 = b2.second - b1.second;
    double B2 = b1.first - b2.first;
    double C2 = A2 * b1.first + B2 * b1.second;

    double det = A1 * B2 - A2 * B1;
    if (abs(det) < 1e-9) {
        return nullopt;
    } else {
        double x = (B2 * C1 - B1 * C2) / det;
        double y = (A1 * C2 - A2 * C1) / det;
        return pdd(x, y);
    }
}

double interpolate(const pdd& a, const pdd& b, double x) {
    if (abs(a.first - b.first) < 1e-9) {
        return a.second;
    }
    double slope = (b.second - a.second) / (b.first - a.first);
    return a.second + slope * (x - a.first);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    k += 2;
    vector<pll> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }

    vector<vector<double>> dp(n, vector<double>(k + 1, 1e12));
    dp[0][1] = 0;
    for (int cur = 1; cur < n; cur++) {
        for (int pre = 0; pre < cur; pre++) {
            for (int used = 2; used <= k; used++) {
                // assume a line from pts[pre] to pts[cur]
                double cur_dp = dp[pre][used - 1];
                pdd a1 = pdd(pts[pre].first, pts[pre].second);
                pdd a2 = pdd(pts[cur].first, pts[cur].second);
                for (int mid = pre; mid < cur; mid++) {
                    pdd b1 = pdd(pts[mid].first, pts[mid].second);
                    pdd b2 = pdd(pts[mid + 1].first, pts[mid + 1].second);
                    auto inter = intersect(a1, a2, b1, b2);
                    // 2 triangles
                    if (inter && inter->first >= pts[mid].first - 1e-9 && inter->first <= pts[mid + 1].first + 1e-9) {
                        cur_dp += abs(pts[mid].second - interpolate(a1, a2, pts[mid].first)) * (inter->first - pts[mid].first) / 2;
                        cur_dp += abs(pts[mid + 1].second - interpolate(a1, a2, pts[mid + 1].first)) * (pts[mid + 1].first - inter->first) / 2;
                    }
                    // 1 trapezoid
                    else {
                        cur_dp += abs(pts[mid].second - interpolate(a1, a2, pts[mid].first) + pts[mid + 1].second - interpolate(a1, a2, pts[mid + 1].first)) * (pts[mid + 1].first - pts[mid].first) / 2;
                    }
                }
                dp[cur][used] = min(dp[cur][used], cur_dp);
            }
        }
    }

    cout << fixed << setprecision(10) << dp[n - 1][k] << "\n";

    return 0;
}