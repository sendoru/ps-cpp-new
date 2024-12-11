// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> get_factors(ll n) {
    vector<ll> ret;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) {
                ret.push_back(n / i);
            }
        }
    }
    return ret;
}

ll solve_naive(ll a, ll b, ll k) {
    if (k >= a || k >= b) {
        return a + b;
    }
    ll ans = 0;
    for (ll i = -k; i <= k; i++) {
        ll aa = a - i;
        ll bb = b + i;
        ans = max(ans, __gcd(aa, bb));
    }

    return ans;
}

ll solve(ll a, ll b, ll k) {
    if (k >= a || k >= b) {
        return a + b;
    }
    ll s = a + b;
    vector<ll> factors = get_factors(s);
    sort(factors.begin(), factors.end(), greater<ll>());
    for (ll f : factors) {
        ll amod = a % f, bmod = b % f;
        if ((amod + bmod) % f == 0 && min(amod, bmod) <= k) {
            return f;
        }
    }

    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    for (ll a = 1; a <= 234; a++) {
        for (ll b = 1; b <= 456; b++) {
            for (ll k = 1; k <= 234; k++) {
                if (solve(a, b, k) != solve_naive(a, b, k)) {
                    cout << "a: " << a << ", b: " << b << ", k: " << k << '\n';
                    cout << "solve: " << solve(a, b, k) << ", solve_naive: " << solve_naive(a, b, k) << '\n';
                }
            }
        }
    }
#endif

    ll a, b, k;
    cin >> a >> b >> k;
    cout << solve(a, b, k) << '\n';

    return 0;
}