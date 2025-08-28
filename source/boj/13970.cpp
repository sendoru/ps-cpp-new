// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll cache[1'000'010];

ll euler_phi(ll n) {
    ll res = n, nn = n;
    for (ll i = 2; i * i <= nn; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n > 1) {
        res -= res / n;
    }
    return res;
}

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = (res * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

vector<ll> real_exps;

// tower[idx] ** (tower[idx + 1] ** (tower[idx + 2] ** ...)) % mod
ll solve(const vector<ll> &tower, int idx, ll mod) {
    if (tower.size() == 0) {
        return 1;
    }
    if (idx == (int)tower.size() - 1) {
        real_exps[idx] = 1;
        return tower[idx] % mod;
    }

    ll exp = solve(tower, idx + 1, cache[mod]);

    if (real_exps[idx + 1] != 0 && real_exps[idx + 1] <= 2e6) {
        real_exps[idx] = 1;
        for (ll i = 0; i < real_exps[idx + 1]; i++) {
            real_exps[idx] *= tower[idx + 1];
            if (real_exps[idx] > 2e6) {
                real_exps[idx] = 0;
                break;
            }
        }
    } else {
        real_exps[idx] = 0;
    }

    if (mod == 1) {
        return 0;
    }
    if (tower[idx] % mod == 0) {
        return 0;
    }

    ll gcd_part = gcd(tower[idx], mod);
    ll div = tower[idx] / gcd_part;

    if (real_exps[idx] != 0 && real_exps[idx] <= 2e6) {
        return modpow(tower[idx], real_exps[idx], mod);
    }
    if (modpow(gcd_part, 2e6, mod) != 0) {
        return modpow(tower[idx], exp + cache[mod], mod);
    }
    ll res = modpow(div, exp, mod);
    res = (res * modpow(gcd_part, real_exps[idx] == 0 ? (ll)2e6 : real_exps[idx], mod)) % mod;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t, mod;
    cin >> t >> mod;
    for (ll i = mod; i > 1;) {
        cache[i] = euler_phi(i);
        i = cache[i];
    }
    cache[1] = 1;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> tower(n);
        for (int i = 0; i < n; i++) {
            cin >> tower[i];
        }
        tower.erase(find(tower.begin(), tower.end(), (ll)1), tower.end());
        n = (ll)tower.size();
        real_exps = vector<ll>(n, 0);
        cout << solve(tower, 0, mod) % mod << '\n';
    }

    return 0;
}