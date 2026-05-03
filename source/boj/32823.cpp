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

double cross(pdd o, pdd a, pdd b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int ccw(pdd a, pdd b, pdd c) {
    double cr = cross(a, b, c);
    if (cr > 0)
        return 1;
    if (cr < 0)
        return -1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<pdd, pdd>> lines(n);
    for (int i = 0; i < n; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        double tr1 = (double)t1 / 1800.0 * M_PI;
        double tr2 = (double)t2 / 1800.0 * M_PI;
        lines[i] = {{1000 * cos(tr1), 1000 * sin(tr1)}, {1000 * cos(tr2), 1000 * sin(tr2)}};
    }
    vector<pdd> p(2);
    for (int i = 0; i < 2; i++) {
        int t, r;
        cin >> t >> r;
        double tr = (double)t / 1800.0 * M_PI;
        p[i] = {r * cos(tr), r * sin(tr)};
    }

    int cross_cnt = 0;
    for (int i = 0; i < n; i++) {
        int ccw1 = ccw(lines[i].first, lines[i].second, p[0]);
        int ccw2 = ccw(lines[i].first, lines[i].second, p[1]);
        if (ccw1 * ccw2 < 0) {
            cross_cnt++;
        }
    }

    cout << ((cross_cnt & 1) ? "NO" : "YES") << "\n";

    return 0;
}