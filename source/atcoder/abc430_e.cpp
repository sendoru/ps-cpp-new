// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll mod_pow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1)
            res = (res * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

ll hash_push_back(ll h, char c, ll len, ll base, ll mod) {
    return (h + c * mod_pow(base, len, mod)) % mod;
}

ll hash_pop_front(ll h, char c, ll len, ll base, ll mod) {
    h = (h - c + mod) % mod;
    h = (h * mod_pow(base, mod - 2, mod)) % mod;
    return h;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;
        int n = a.size();
        ll a_hash1 = 0, a_hash2 = 0;
        ll b_hash1 = 0, b_hash2 = 0;
        ll base1 = 131, base2 = 137;
        ll mod1 = MOD1, mod2 = MOD9;
        for (int i = 0; i < n; i++) {
            char c = a[i];
            a_hash1 = hash_push_back(a_hash1, c, i, base1, mod1);
            a_hash2 = hash_push_back(a_hash2, c, i, base2, mod2);
        }
        for (int i = 0; i < n; i++) {
            char c = b[i];
            b_hash1 = hash_push_back(b_hash1, c, i, base1, mod1);
            b_hash2 = hash_push_back(b_hash2, c, i, base2, mod2);
        }
        ll ans = 0;
        while (!(a_hash1 == b_hash1 && a_hash2 == b_hash2)) {
            char front = a[ans];
            a_hash1 = hash_pop_front(a_hash1, front, n, base1, mod1);
            a_hash2 = hash_pop_front(a_hash2, front, n, base2, mod2);
            a_hash1 = hash_push_back(a_hash1, front, n - 1, base1, mod1);
            a_hash2 = hash_push_back(a_hash2, front, n - 1, base2, mod2);
            ans++;
            if (ans > n) {
                ans = -1;
                break;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}