// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll isqrt(ll x) {
    ll l = 0, h = 1e9 + 1;
    while (l < h) {
        ll mid = (l + h + 1) / 2;
        if (mid * mid <= x) {
            l = mid;
        } else {
            h = mid - 1;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        bool ans = false;
        ll root = isqrt(n);
        if (root * root == n) {
            ans = true;
        } else {
            for (ll i = 2; i * i * i <= 2 * n + 10; i++) {
                ll sq = i * i;
                ll div = n / sq;
                ll rem = n % sq;
                ll sqrt_div = isqrt(div);
                if (n % (i * i) == 0 || (sqrt_div * sqrt_div == div && rem == 0)) {
                    ans = true;
                    break;
                }
            }
        }
        cout << (ans ? "yes\n" : "no\n");
    }

    return 0;
}