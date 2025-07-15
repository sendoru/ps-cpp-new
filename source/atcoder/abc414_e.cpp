// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    b %= m;
    while (e > 0) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}
ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;

    ll nm9 = n % MOD9;

    ll ans = nm9 * nm9 % MOD9;
    ans -= nm9 * (nm9 - 1) % MOD9 * modinv(2, MOD9) % MOD9;
    ans = (ans + MOD9) % MOD9;

    ll sqrt_n = sqrt(n);

    for (ll i = 1; i <= sqrt_n; i++) {
        ans -= (n / i) % MOD9;
        ans = (ans + MOD9) % MOD9;
    }
    ll binsearch_max = n / sqrt_n;
    ll prev = sqrt_n;
    // using binary search,
    // we can find count of i s.t. n // i == k for k in [1, binsearch_max]
    for (ll k = binsearch_max; k >= 1; k--) {
        // val = max i s.t. n // i == k
        ll val = prev;
        ll lo = prev, hi = n;
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            if (n / mid < k) {
                hi = mid - 1;
            } else {
                val = max(val, mid);
                lo = mid + 1;
            }
        }
        ll count = val - prev;
        ans -= k * count % MOD9;
        ans = (ans + MOD9) % MOD9;
        prev = val;
    }

    ans = (ans + MOD9) % MOD9;
    cout << ans << endl;

    return 0;
}