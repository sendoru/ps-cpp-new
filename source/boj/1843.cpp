#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve_a(int n) {
    ll ret = 0;
    for (int i = 3; i <= n; i++) {
        ret += i / 2 - (i % 2 == 0);
    }
    return ret;
}

ll solve_b(int n) {
    ll ret = 0;

    vector<int> factors;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
        }
    }
    for (int i = 0; i < factors.size(); i++) {
        for (int j = i; j < factors.size(); j++) {
            if (n % (factors[i] + factors[j]) == 0) {
                ret++;
            }
        }
    }

    return ret;
}

ll solve_c(int n) {
    ll ret = 0;
    vector<ll> is_prime(n + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * 2; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    for (int i = 3; i <= n - 2; i++) {
        if (is_prime[i] && is_prime[i + 2]) {
            ret++;
        }
    }

    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    cout << solve_a(n) << '\n';
    cout << solve_b(n) << '\n';
    cout << solve_c(n) << '\n';

    return 0;
}