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

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    b %= m;
    while (e > 0) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

ll k_one_mod(ll k, ll m) {
    // return (modpow(10, k, m) + m - 1) % m * modinv(9, m) % m;
    // ^ this does not work when m is divisible by 9
    if (k == 0) {
        return 0;
    }
    if (k == 1) {
        return 1 % m;
    }
    ll half_res = k_one_mod(k / 2, m);
    ll res = half_res * modpow(10, k / 2, m) % m;
    res = (res + half_res) % m;
    if (k % 2 == 1) {
        res = res * 10 % m;
        res = (res + 1) % m;
    }
    return res;
}

ll mod_runlen(vector<pll> &runlen, ll m) {
    ll res = 0;
    for (auto [digit, len] : runlen) {
        res = res * modpow(10, len, m) % m;
        res = (res + digit * k_one_mod(len, m)) % m;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll k, m;
    cin >> k >> m;
    vector<pll> runlen(k);
    for (int i = 0; i < k; i++) {
        cin >> runlen[i].first >> runlen[i].second;
    }

    ll nmmod = mod_runlen(runlen, MOD);
    ll minv = modinv(m, MOD);
    ll nmm = mod_runlen(runlen, m);
    ll ans = (nmmod - nmm + MOD) % MOD * minv % MOD;
    cout << ans << '\n';

    return 0;
}