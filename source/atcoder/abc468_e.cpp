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
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll x, ll m) {
    return modpow(x, m - 2, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    vector<ll> pf_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pf_sum[i + 1] = (pf_sum[i] + a[i]) % MOD9;
    }

    ll cur_sum = 0;
    for (int len = 1; len <= n / 2; len++) {
        cur_sum = (cur_sum + pf_sum[n - len + 1] - pf_sum[len - 1] + MOD9) % MOD9;
        ans = (ans + cur_sum * modinv(len, MOD9)) % MOD9;
        ans = (ans + cur_sum * modinv(n - len + 1, MOD9)) % MOD9;
    }
    if (n % 2 == 1) {
        cur_sum = (cur_sum + a[n / 2]) % MOD9;
        ans = (ans + cur_sum * modinv(n / 2 + 1, MOD9)) % MOD9;
    }

    cout << ans;

    return 0;
}