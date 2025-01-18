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

    ll r;
    cin >> r;
    ll ans = 0;

    for (ld y = -r + .5; y < r - .5; y++) {
        ld y_nxt = y + 1;
        ld x = sqrt(r * r - y * y);
        ll x_double = 2 * x;
        if (x_double % 2 == 0) {
            x_double--;
        }
        ld x_nxt = sqrt(r * r - y_nxt * y_nxt);
        ll x_nxt_double = 2 * x_nxt;
        if (x_nxt_double % 2 == 0) {
            x_nxt_double--;
        }

        ll line_cnt = max(0ll, min(x_double, x_nxt_double));
        ans += line_cnt;
    }

    cout << ans << endl;

    return 0;
}