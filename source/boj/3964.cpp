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
        ll n, k;
        cin >> n >> k;

        // 1. factorize k
        map<ll, int> factors;
        for (ll i = 2; i * i <= k; i++) {
            while (k % i == 0) {
                factors[i]++;
                k /= i;
            }
        }
        if (k > 1) {
            factors[k]++;
        }

        ll ans = 1e18;
        for (auto [p, e] : factors) {
            ll cnt = 0;
            for (__int128_t i = p; i <= n; i *= p) {
                cnt += n / i;
            }
            ans = min(ans, cnt / e);
        }

        cout << ans << '\n';
    }

    return 0;
}