// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    b %= m;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            a[i][j]--;
        }
    }

    ll ans = n * modpow(m, n, MOD9) % MOD9;
    vector<ll> cnt(n * m);
    for (int i = 0; i < n; i++) {
        ll prev = modpow(m, i, MOD9);
        ll later = modpow(m, n - i - 1, MOD9);
        auto new_cnt = cnt;
        for (int j = 0; j < n * m; j++) {
            new_cnt[j] = cnt[j] * m % MOD9;
        }
        for (int j = 0; j < m; j++) {
            ans -= later * cnt[a[i][j]] % MOD9;
            ans = (ans + MOD9) % MOD9;
            new_cnt[a[i][j]] += (prev - cnt[a[i][j]] + MOD9) % MOD9;
            new_cnt[a[i][j]] %= MOD9;
        }
        cnt = new_cnt;
    }

    cout << ans << "\n";

    return 0;
}