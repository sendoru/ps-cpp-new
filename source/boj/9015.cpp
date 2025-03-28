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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pll> dots(n);
        for (int i = 0; i < n; i++) {
            cin >> dots[i].x >> dots[i].y;
            dots[i].x += 12345;
            dots[i].y += 12345;
        }
        unordered_set<ll> s;
        for (int i = 0; i < n; i++) {
            s.insert((dots[i].x << 32) | dots[i].y);
        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double xm = (dots[i].x + dots[j].x) / 2.0;
                double ym = (dots[i].y + dots[j].y) / 2.0;
                double dx = dots[j].x - dots[i].x;
                double dy = dots[j].y - dots[i].y;

                double x3 = xm + dy / 2.0;
                double y3 = ym - dx / 2.0;
                ll x3i = round(x3);
                ll y3i = round(y3);
                if (abs(x3 - x3i) >= 1e-6 && abs(y3 - y3i) >= 1e-6) {
                    continue;
                }

                double x4 = xm - dy / 2.0;
                double y4 = ym + dx / 2.0;
                ll x4i = round(x4);
                ll y4i = round(y4);
                if (abs(x4 - x4i) >= 1e-6 && abs(y4 - y4i) >= 1e-6) {
                    continue;
                }

                if (s.count((x3i << 32) | y3i) && s.count((x4i << 32) | y4i)) {
                    ans = max(ans, (ll)(dx * dx + dy * dy) / 2);
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}