// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef __int128_t ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long n;
    cin >> n;

    ll ans = 0;
    ll fact = 2;
    for (ll len = 3; len <= 20; len++) {
        fact *= len;
        if (fact > n) {
            break;
        }

        ll a1_max = powl(n, (ld)1.0 / len) + 1;
        for (ll a1 = 1; a1 <= a1_max; a1++) {
            ll d1_l = 1, d1_r = powl(n, (ld)1.0 / (len - 1)) + 1, d1 = 0;
            while (d1_l <= d1_r) {
                ll d1_mid = (d1_l + d1_r) / 2;
                ll cur = a1;
                ll prod = 1;
                for (int i = 0; i < len; i++) {
                    prod *= cur;
                    cur += d1_mid;
                    if (prod > n) {
                        break;
                    }
                }
                if (prod <= n) {
                    d1_l = d1_mid + 1;
                    d1 = max(d1, d1_mid);
                } else {
                    d1_r = d1_mid - 1;
                }
            }
            ans += d1;
        }
    }

    cout << (long long)ans;

    return 0;
}