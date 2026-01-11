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

    ll k;
    cin >> k;

    k -= 6;
    ll ans = 0;
    for (ll i1 = 0; i1 <= k; i1++) {
        for (ll i2 = 0; i1 + i2 <= k; i2++) {
            ll i3 = k - i1 - i2;
            ll c1 = i1 + i2;
            ll c2 = i2 + i3;
            ll c3 = i3 + i1;
            ans += (i1 + 1) * (i2 + 1) % MOD9 * (i3 + 1) % MOD9 * (min({c1, c2, c3}) + 4) % MOD9;
            ans %= MOD9;
        }
    }

    cout << ans;

    return 0;
}