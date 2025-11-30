// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<ll>> mods(12, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        mods[0][i] = a[i] % m;
    }
    for (int k = 1; k < 12; k++) {
        for (int i = 0; i < n; i++) {
            mods[k][i] = (mods[k - 1][i] * 10) % m;
        }
    }
    map<pll, ll> cnt;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < n; j++) {
            cnt[make_pair(mods[i][j], i)]++;
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll digit = 0;
        ll x = a[i];
        while (x) {
            digit++;
            x /= 10;
        }
        ll need = (m - (a[i] % m)) % m;
        ans += cnt[make_pair(need, digit)];
        // if ((mods[digit][i] + a[i]) % m == 0) {
        //     ans--;
        // }
    }

    cout << ans << "\n";

    return 0;
}