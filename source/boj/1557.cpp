// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll WTF = 901800900;

// from a vector of numbers,
// pick products of cnt numbers with maximum product prod_max
// assuming v is sorted in non-decreasing order
vector<ll>
pick_prods(vector<ll> &v, ll cnt, ll prod_max) {
    vector<ll> prods;
    ll n = v.size();

    function<void(ll, ll, ll)> dfs = [&](ll idx, ll cnt, ll prod) {
        if (cnt == 0) {
            prods.push_back(prod);
            return;
        }
        if (idx + cnt > n) {
            return;
        }

        for (ll i = idx; i < n; i++) {
            if (i != n - 1 && cnt >= 2 && prod * v[i] * v[i + 1] > prod_max) {
                break;
            }
            if (prod * v[i] > prod_max) {
                break;
            }
            dfs(i + 1, cnt - 1, prod * v[i]);
        }
    };

    dfs(0, cnt, 1);

    return prods;
}

vector<ll> sieve(ll n) {
    vector<bool> is_prime(n + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    vector<ll> primes;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll k;
    cin >> k;

    vector<ll> primes = sieve(1e5);
    vector<ll> prime_squares;
    for (ll prime : primes) {
        prime_squares.push_back(prime * prime);
    }

    // find count of square-free numbers less than or equal to x
    ll lo = 1, hi = 1e10;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        ll cnt = mid;
        for (int i = 1; i <= 6; i++) {
            vector<ll> prods = pick_prods(prime_squares, i, mid);
            if (prods.empty()) {
                break;
            }
            for (ll prod : prods) {
                cnt -= (i % 2 == 1 ? 1 : -1) * mid / prod;
            }
        }
        if (cnt < k) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    cout << lo << '\n';

    return 0;
}