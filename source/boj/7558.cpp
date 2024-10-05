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
    if (e == 0) {
        return 1;
    }
    if (e % 2) {
        return b * modpow(b, e - 1, m) % m;
    }
    ll half = modpow(b, e / 2, m);
    return half * half % m;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        ll a, p;
        cin >> a >> p;
        a = (a % p + p) % p;

        ll ans = modpow(a, (p - 1) / 2, p);
        cout << "Scenario #" << t << ":\n";
        cout << (ans == 1 ? 1 : -1) << "\n\n";
    }

    return 0;
}