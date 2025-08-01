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
    int q;
    cin >> q;
    while (q--) {
        ll n, x, y;
        cin >> n >> x >> y;
        ll l = n * y / (x + y);
        ll r = n * y / (x + y);
        if (n * y % (x + y) != 0) {
            r++;
        }
        if (l == r) {
            cout << 1 << '\n';
            cout << l << ' ' << x + y << '\n';
        } else {
            ll b = n * y - (x + y) * l;
            ll a = x + y - b;
            cout << 2 << '\n';
            cout << l << ' ' << a << '\n';
            cout << r << ' ' << b << '\n';
        }
    }

    return 0;
}