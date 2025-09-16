// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MOD = 10007;

ll comb[60][60];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i < 60; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }

    int n;
    cin >> n;

    ll ans = 0;
    for (int i = 1; n - 4 * i >= 0; i++) {
        ans += comb[13][i] * comb[52 - 4 * i][n - 4 * i] * (i & 1 ? 1 : -1);
        ans = (ans % MOD + MOD) % MOD;
    }

    cout << ans;

    return 0;
}