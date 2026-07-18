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

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        ll isqrtn = (ll)sqrtl(n);
        ll remain = n - isqrtn * isqrtn;
        ll ans = 2 * isqrtn * (isqrtn - 1);
        if (remain > 0 && remain <= isqrtn) {
            ans += 2 * remain - 1;
        } else if (remain > 0) {
            ans += 2 * isqrtn - 1;
            remain -= isqrtn;
            ans += 2 * remain - 1;
        }
        cout << ans << '\n';
    }

    return 0;
}