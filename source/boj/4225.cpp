// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ld line_dot_dist(pii p1, pii p2, pii q) {
    // ax + by + c = 0
    ld a = p2.y - p1.y;
    ld b = p1.x - p2.x;
    ld c = (ld)p2.x * p1.y - (ld)p1.x * p2.y;
    return abs(a * q.x + b * q.y + c) / sqrt(a * a + b * b);
}

int ccw(pii a, pii b, pii c) {
    ll area = (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
    if (area > 0)
        return 1;
    if (area < 0)
        return -1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<pii> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i].x >> p[i].y;
        }

        sort(p.begin(), p.end());
        sort(p.begin() + 1, p.end(), [&](pii a, pii b) {
            int dir = ccw(p[0], a, b);
            if (dir != 0)
                return dir > 0;
            return a < b;
        });
        vector<pii> hull;
        hull.push_back(p[0]);
        hull.push_back(p[1]);
        for (int i = 2; i < n; i++) {
            while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i]) <= 0) {
                hull.pop_back();
            }
            hull.push_back(p[i]);
        }
        int m = hull.size();
        ld ans = 1e18;
        for (int i = 0; i < m; i++) {
            ld cur = 0;
            for (int j = 0; j < m; j++) {
                cur = max(cur, line_dot_dist(hull[i], hull[(i + 1) % m], hull[j]));
            }
            ans = min(ans, cur);
        }
        cout << "Case " << t << ": " << fixed << setprecision(2) << ans + 0.005 - 1e-9 << '\n';
        t++;
    }

    return 0;
}