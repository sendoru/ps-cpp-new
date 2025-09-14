// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef __int128_t i128;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll comb[22][22], dp[22];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i <= 20; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }

    ll n, m, y;
    cin >> n >> m >> y;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dp[m] = 1;
    dp[m + 1] = -(m + 1);
    for (int i = m + 2; i <= n; i++) {
        dp[i] = -comb[i][m];
        for (int j = m + 1; j < i; j++) {
            dp[i] -= comb[i][j] * dp[j];
        }
    }

    ll ans = 0;

    for (int j = 0; j < (1 << n); j++) {
        if (__builtin_popcount(j) < m)
            continue;
        i128 lcm = 1;
        for (int k = 0; k < n; k++) {
            if (j & (1 << k)) {
                lcm = lcm / gcd(lcm, (i128)a[k]) * a[k];
                if (lcm > y)
                    break;
            }
        }
        if (lcm > y)
            continue;
        ans += (y / lcm) * dp[__builtin_popcount(j)];
    }

    cout << ans << '\n';

    return 0;
}