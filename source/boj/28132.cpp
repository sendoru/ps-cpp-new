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

    int n;
    cin >> n;
    vector<pii> dots(n);
    map<pii, int> cnt;
    int zero_cnt = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        dots[i] = {x, y};
        if (x == 0 && y == 0) {
            zero_cnt++;
        } else {
            int gcd = __gcd(abs(x), abs(y));
            x /= gcd;
            y /= gcd;
            if (x < 0) {
                x = -x;
                y = -y;
            } else if (x == 0) {
                y = abs(y);
            }
            cnt[{x, y}]++;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (dots[i].x == 0 && dots[i].y == 0) {
            continue;
        }
        int x = dots[i].y, y = -dots[i].x;
        int gcd = __gcd(abs(x), abs(y));
        x /= gcd;
        y /= gcd;
        if (x < 0) {
            x = -x;
            y = -y;
        } else if (x == 0) {
            y = abs(y);
        }

        if (cnt.count({x, y})) {
            ans += cnt[{x, y}];
        }
    }
    ans /= 2;
    ans += (ll)zero_cnt * (n - zero_cnt);
    ans += (ll)zero_cnt * (zero_cnt - 1) / 2;

    cout << ans << "\n";

    return 0;
}