// #include "atcoder/all"
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e)
{
    ll ret = 1;
    while (e > 0) {
        if (e & 1) {
            ret = (ret * b) % MOD1;
        }
        b = (b * b) % MOD1;
        e >>= 1;
    }

    return ret;
}

ll modInv(ll a) { return modpow(a, MOD1 - 2); }

ll fact(ll n)
{
    ll ret = 1;
    for (ll i = 1; i <= n; i++) {
        ret = (ret * i) % MOD1;
    }

    return ret;
}

ll solve(ll n, ll k)
{
    ll nfact = fact(n);
    if (n % k == 0) {
        ll den = modpow(fact(n / k), k);
        return (nfact * modInv(den)) % MOD1;
    }
    ll den = modpow(fact(n / k), k - n % k);
    den = (den * modpow(fact(n / k + 1), n % k)) % MOD1;
    return (nfact * modInv(den)) % MOD1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    cout << solve(n, k) << endl;

    return 0;
}