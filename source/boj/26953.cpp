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

vector<int> phi(222'222);
vector<int> primes;

void eratos() {
    vector<bool> is_prime(222'222, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < 222'222; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j < 222'222; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

ll ephi(ll n) {
    ll ret = n;
    for (auto i : primes) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            ret -= ret / i;
        }
        if (i * i > n) {
            break;
        }
    }
    if (n > 1) {
        ret -= ret / n;
    }
    return ret;
}

ll ephi2(ll n, ll max) {
    if (max >= n) {
        return (max / n) * phi[n] + ephi2(n, max % n);
    }
    if (max < 1) {
        return 0;
    }
    vector<ll> prime_factors;
    ll temp = n;
    for (auto i : primes) {
        if (temp % i == 0) {
            prime_factors.push_back(i);
            while (temp % i == 0) {
                temp /= i;
            }
        }
        if (i * i > temp) {
            break;
        }
    }
    if (temp > 1) {
        prime_factors.push_back(temp);
    }
    ll pf_size = prime_factors.size();
    ll res = max;
    for (int bit = 1; bit < (1 << pf_size); bit++) {
        ll mul = 1;
        for (int j = 0; j < pf_size; j++) {
            if (bit & (1 << j)) {
                mul *= prime_factors[j];
            }
        }
        ll cnt = max / mul;
        if (__builtin_popcount(bit) % 2 == 1) {
            res -= cnt;
        } else {
            res += cnt;
        }
    }
    return res;
}

vector<ll> get_divs(ll n) {
    vector<ll> res;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i != n) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}

ll solve_naive(ll M, ll b) {
    ll ans = 0;
    for (ll a = 1; a <= M; a++) {
        for (ll m = 2; m <= M; m++) {
            if (b % gcd(a, m) == 0) {
                ans++;
            }
        }
    }
    return ans;
}

ll solve(ll M, ll b) {
    ll ans = 0;
    for (ll m = 2; m <= M; m++) {
        ll bmm = b % m;
        ll g = gcd(bmm, m);
        if (bmm == 0) {
            ans += M;
            continue;
        }
        auto divs = get_divs(g);
        for (ll d : divs) {
            ll mdd = m / d;
            // ans += (M / m) * phi[mdd];
            ans += ephi2(mdd, M / d);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    eratos();
    for (int i = 1; i < 222'222; i++) {
        phi[i] = ephi(i);
    }

    ll M, b;
    cin >> M >> b;

    ll ans = solve(M, b);
#ifdef DEBUG
    ll ans2 = solve_naive(M, b);
    assert(ans == ans2);
#endif
    cout << ans << '\n';

    return 0;
}