// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pll> hull;
    for (int i = 0; i < n; i++) {
        ll x, y;
        char c;
        cin >> x >> y >> c;
        if (c == 'Y') {
            hull.emplace_back(x, y);
        }
    }

    pld center;
    for (int i = 0; i < hull.size(); i++) {
        center.x += hull[i].x;
        center.y += hull[i].y;
    }
    center.x /= hull.size();
    center.y /= hull.size();

    auto cmp = [&](pld a, pld b) {
        ld theta_a = atan2(a.y - center.y, a.x - center.x);
        ld theta_b = atan2(b.y - center.y, b.x - center.x);
        return theta_a < theta_b;
    };

    sort(hull.begin(), hull.end(), cmp);
    cout << hull.size() << "\n";
    auto it = min_element(hull.begin(), hull.end());
    for (auto i = it; i != hull.end(); i++) {
        cout << i->x << " " << i->y << "\n";
    }
    for (auto i = hull.begin(); i != it; i++) {
        cout << i->x << " " << i->y << "\n";
    }

    return 0;
}