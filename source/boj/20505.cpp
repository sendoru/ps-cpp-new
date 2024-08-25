#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    if (e == 0)
        return 1;
    if (e % 2)
        return b * modpow(b, e - 1, m) % m;
    ll h = modpow(b, e / 2, m);
    return h * h % m;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string n;
    cin >> n;
    reverse(n.begin(), n.end());
    ll ans = 0;
    for (int i = 0; i < n.size(); i++) {
        int d = n[i] - '0';
        ans += modpow(2, n.size() - i - 1, MOD9) * modpow(11, i, MOD9) % MOD9 * d % MOD9;
        ans %= MOD9;
    }

    cout << ans << '\n';

    return 0;
}