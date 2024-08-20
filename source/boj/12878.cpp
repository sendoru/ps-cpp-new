#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll mod)
{
    if (e == 0)
        return 1;
    if (e % 2)
        return modpow(b, e - 1, mod) * b % mod;
    ll m = modpow(b, e / 2, mod);
    return m * m % mod;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    if (n == 1) {
        cout << 2;
    }
    else {
        cout << (modpow(2, n - 1, 10007) + modpow(2, 2 * n - 2, 10007)) % 10007;
    }

    return 0;
}