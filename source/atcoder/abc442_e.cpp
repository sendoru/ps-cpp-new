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

int ccw(const pll &a, const pll &b, const pll &c) {
    pll ab = {b.x - a.x, b.y - a.y};
    pll ac = {c.x - a.x, c.y - a.y};
    ll cross = ab.x * ac.y - ab.y * ac.x;
    if (cross > 0)
        return 1;
    else if (cross < 0)
        return -1;
    else
        return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<pll> dots(n);
    for (int i = 0; i < n; i++) {
        cin >> dots[i].x >> dots[i].y;
        ll g = gcd(abs(dots[i].x), abs(dots[i].y));
        dots[i].x /= g;
        dots[i].y /= g;
    }

    vector<pll> dots2 = dots;
    // angle sorting
    sort(dots2.begin(), dots2.end(), [](const pll &a, const pll &b) {
        return atan2l(a.y, a.x) < atan2l(b.y, b.x);
    });

    while (q--) {
        ll a, b;
        cin >> a >> b;
        auto p1 = dots[b - 1];
        auto p2 = dots[a - 1];
        auto lb = lower_bound(dots2.begin(), dots2.end(), p1, [](const pll &a, const pll &b) {
            return atan2l(a.y, a.x) < atan2l(b.y, b.x);
        });
        auto ub = upper_bound(dots2.begin(), dots2.end(), p2, [](const pll &a, const pll &b) {
            return atan2l(a.y, a.x) < atan2l(b.y, b.x);
        });
        ll ans = ub - lb;
        if (ans <= 0)
            ans += n;
        cout << ans << "\n";
    }

    return 0;
}