// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;

    for (ll i = 1; i * i * i <= n; i++) {
        if (n % i == 0) {
            ll j = n / i;
            ld det = (ld)9 * i * i - 12 * (ld)(i * i - j);
            if (det < 0) {
                continue;
            }
            if (sqrt(det) != (ll)sqrt(det)) {
                continue;
            }
            ll num = (ld)-3 * i + sqrt(det);
            if (num % 6 == 0 && num / 6 > 0) {
                cout << num / 6 + i << ' ' << num / 6;
                return 0;
            }
        }
    }

    cout << -1;

    return 0;
}