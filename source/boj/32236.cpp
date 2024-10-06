// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m)
{
    ll ret = 1;
    while (e > 0) {
        if (e & 1) {
            ret = (ret * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return ret;
}

ll modinv(ll a, ll m)
{
    return modpow(a, m - 2, m);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    ll cur = 1;
    vector<ll> ans = {cur};
    for (int i = 2; i <= n; i++) {
        cur = cur + modpow(modinv(i, MOD1), m, MOD1);
        cur %= MOD1;
        ans.push_back(cur);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}