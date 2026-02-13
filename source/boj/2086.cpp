// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MOD = 1'000'000'000;

array<ll, 4> matmul_22(array<ll, 4> &a, array<ll, 4> &b, ll mod) {
    array<ll, 4> res = {0, 0, 0, 0};
    res[0] = (a[0] * b[0] % mod + a[1] * b[2] % mod) % mod;
    res[1] = (a[0] * b[1] % mod + a[1] * b[3] % mod) % mod;
    res[2] = (a[2] * b[0] % mod + a[3] * b[2] % mod) % mod;
    res[3] = (a[2] * b[1] % mod + a[3] * b[3] % mod) % mod;
    return res;
}

array<ll, 4> matpow_22(array<ll, 4> &m, ll e, ll mod) {
    array<ll, 4> res = {1, 0, 0, 1};
    array<ll, 4> base = m;
    while (e) {
        if (e & 1) {
            res = matmul_22(res, base, mod);
        }
        base = matmul_22(base, base, mod);
        e >>= 1;
    }
    return res;
}

ll fib(ll n, ll mod) {
    if (n == 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    array<ll, 4> m = {1, 1, 1, 0};
    array<ll, 4> res = matpow_22(m, n - 1, mod);
    return res[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, b;
    cin >> a >> b;

    ll fib_b_sum = fib(b + 2, MOD) - 1;
    ll fib_a_sum = fib(a + 1, MOD) - 1;
    ll ans = (fib_b_sum - fib_a_sum + MOD) % MOD;
    cout << ans << "\n";

    return 0;
}