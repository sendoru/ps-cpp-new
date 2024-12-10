// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<bool> erathos(int n)
{
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    ll ans = 0;
    vector<bool> is_prime = erathos(4 * 1e6);
    // p ^ 8

    for (int i = 2; i <= 4 * 1e6; i++) {
        if (!is_prime[i]) {
            continue;
        }
        ll pow_by_8 = powl(i, 8);
        if (pow_by_8 > n) {
            break;
        }
        ans++;
    }

    // p1 ^ 2 * p2 ^ 2
    vector<ll> prime_squares;
    for (int i = 2; i <= 4 * 1e6; i++) {
        if (!is_prime[i]) {
            continue;
        }
        ll pow_by_2 = powl(i, 2);
        if (pow_by_2 > n) {
            break;
        }
        prime_squares.push_back(pow_by_2);
    }

    for (int i = 0; i < prime_squares.size(); i++) {
        ll upper_limit = n / prime_squares[i];
        auto it = upper_bound(prime_squares.begin(), prime_squares.end(), upper_limit);

        if (it <= prime_squares.begin() + i) {
            break;
        }
        ans += (ll)distance(prime_squares.begin() + i, it) - 1;
    }

    cout << ans << endl;

    return 0;
}