// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MAX = 5e5 + 10;

vector<ll> pow2;
vector<ll> fact;
vector<ll> inv_fact;
vector<ll> inv;

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

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pow2.resize(MAX);
    pow2[0] = 1;
    for (ll i = 1; i < MAX; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD9;
    }
    fact.resize(MAX);
    fact[0] = 1;
    for (ll i = 1; i < MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MOD9;
    }
    inv_fact.resize(MAX);
    inv_fact[MAX - 1] = modinv(fact[MAX - 1], MOD9);
    for (ll i = MAX - 2; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD9;
    }

    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        vector<ll> a(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }

        ll ans = fact[n - k] * (pow2[n] - 1) % MOD9;
        ll a_max = 0;
        for (auto ai : a) {
            if (ai > a_max) {
                a_max = ai;
                ans = (ans - fact[n - k] * pow2[ai - 1] % MOD9);
                ans = (ans + MOD9) % MOD9;
            }
        }

        for (ll i = a_max + 1; i <= n; i++) {
            ans = (ans - fact[n - k] * modinv(n - i + 1, MOD9) % MOD9 * pow2[i - 1]) % MOD9;
            ans = (ans + MOD9) % MOD9;
        }

        cout << ans << "\n";
    }

    return 0;
}