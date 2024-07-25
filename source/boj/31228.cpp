// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n, k;
    cin >> n >> k;
    ll gcd_nk = __gcd(n, k);

    n /= gcd_nk;
    k /= gcd_nk;
    k = min(k, n - k);

    cout << n * (k - 1);

    return 0;
}