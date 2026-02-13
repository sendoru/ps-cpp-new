// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

lll modpow(lll b, lll e, lll m) {
    lll res = 1;
    while (e) {
        if (e & 1)
            res = (res * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

// 1 + r + r^2 + ... + r^(n - 1) mod m
lll geo_series_sum(lll r, lll n, lll m) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    lll half = geo_series_sum(r, n / 2, m);
    lll res = (half + half * modpow(r, n / 2, m)) % m;
    if (n & 1) {
        res = (1 + r * res) % m;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll m, a, c, x0, n, g;
    cin >> m >> a >> c >> x0 >> n >> g;

    if (a == 1) {
        ll xn = ((lll)x0 + (lll)c * (n % m)) % m;
        cout << xn % g << "\n";
    } else {
        lll apn = modpow(a, n, m);
        lll geo_sum = geo_series_sum(a, n, m);
        lll xn = apn * x0 % m;
        xn = (xn + c * geo_sum) % m;
        cout << (ll)xn % g << "\n";
    }

    return 0;
}