// #include "atcoder/all"
#include <bits/stdc++.h>
#pragma GCC optimize("O3,fast-math,unroll-loops")
#pragma GCC target("avx2,fma")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll x, ll n, ll m) {
    ll ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * x % m;
        }
        x = x * x % m;
        n >>= 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, p;
    cin >> n >> p;
    if (n <= p / 2) {

        ll a[8] = {1, 1, 1, 1, 1, 1, 1, 1};
        ll i;
#pragma omp simd
        for (i = 1; i + 7 <= n; i += 8) {
#pragma omp simd
            for (ll j = 0; j < 8; j++) {
                a[j] = a[j] * (i + j) % p;
            }
        }

        ll ans = 1;
        for (ll j = 0; j < 8; j++) {
            ans = ans * a[j] % p;
        }

        for (; i <= n; i++) {
            ans = ans * i % p;
        }

        cout << ans << '\n';
    }

    else {
        ll a[8] = {1, 1, 1, 1, 1, 1, 1, 1};
        ll i;
#pragma omp simd
        for (i = n + 1; i + 7 <= p - 1; i += 8) {
#pragma omp simd
            for (ll j = 0; j < 8; j++) {
                a[j] = a[j] * (i + j) % p;
            }
        }

        ll ans = 1;
        for (ll j = 0; j < 8; j++) {
            ans = ans * a[j] % p;
        }

        for (; i <= p - 1; i++) {
            ans = ans * i % p;
        }

        cout << modpow(p - ans, p - 2, p) << '\n';
    }

    return 0;
}
