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

    ll n;
    cin >> n;
    vector<ll> l(n);
    for (ll i = 0; i < n; i++) {
        cin >> l[i];
    }

    ll ans = 0;
    for (ll mask = 0; mask < (1 << n); mask++) {
        ll cpos = 1;
        ll cans = 0;
        for (ll i = 0; i < n; i++) {
            ll npos = cpos;
            if ((mask >> i) & 1) {
                npos += 2 * l[i];
            } else {
                npos -= 2 * l[i];
            }
            if ((npos < 0 && cpos > 0) || (npos > 0 && cpos < 0)) {
                cans++;
            }
            cpos = npos;
        }
        ans = max(ans, cans);
    }

    cout << ans << '\n';

    return 0;
}