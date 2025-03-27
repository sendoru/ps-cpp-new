// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(ll n, ll k) {
    if (n == 1) {
        return 0;
    }

    if (k == 1) {
        return n - 1;
    }

    if (k > n) {
        return (solve(n - 1, k) + k) % n;
    }

    ll res = solve(n - n / k, k);
    res -= n % k;
    if (res < 0) {
        res += n;
    } else {
        res += res / (k - 1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    cout << solve(n, k) + 1 << '\n';

    return 0;
}