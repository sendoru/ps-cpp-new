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

ll naive(ll a, ll b) {
    ll min_lcm = 2e18;
    ll ans = 0;
    for (ll i = 1; i <= 10000; i++) {
        ll gcd = __gcd(a + i, b + i);
        ll lcm = (a + i) / gcd * (b + i);
        if (lcm < min_lcm) {
            min_lcm = lcm;
            ans = i;
        }
    }

    return ans;
}

ll solve(ll a, ll b) {
    a++;
    b++;
    if (a > b) {
        swap(a, b);
    }

    ll min_lcm = 2e18;
    ll ans = 0;
    ll diff = b - a;

    if (diff == 0) {
        return 1ll;
    }

    vector<ll> diff_divisors;
    for (int i = 1; i * i <= diff; i++) {
        if (diff % i == 0) {
            diff_divisors.push_back(i);
            if (i != diff / i) {
                diff_divisors.push_back(diff / i);
            }
        }
    }

    for (auto div : diff_divisors) {
        // set minimum n s.t. (a + n) % div == 0
        ll n = (div - a % div) % div;
        ll new_a = a + n;
        ll gcd = __gcd(new_a, diff);
        ll lcm = new_a / gcd * diff;
        if (lcm < min_lcm) {
            min_lcm = lcm;
            ans = n;
        } else if (lcm == min_lcm) {
            ans = min(ans, n);
        }
    }

    return ans + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef DEBUG
    for (ll a = 1; a <= 234; a++) {
        for (ll b = 1; b <= 234; b++) {
            ll expected = naive(a, b);
            ll actual = solve(a, b);
            if (expected != actual) {
                cout << "a: " << a << ", b: " << b << ", expected: " << expected << ", actual: " << actual << '\n';
            }
        }
    }
    cout << "Done\n";

#else
    ll a, b;
    cin >> a >> b;
    cout << solve(a, b);
#endif

    return 0;
}