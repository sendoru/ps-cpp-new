// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll a, ll b, ll mod) {
    ll ret = 1;
    while (b) {
        if (b & 1) {
            ret = ret * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

// hash
pll add_left(pll a, char c) {
    return {(a.first * 26 + c) % MOD1, (a.second * 26 + c) % MOD9};
}

pll add_right(pll a, char c, int len) {
    return {(a.first + c * modpow(26, len, MOD1)) % MOD1, (a.second + c * modpow(26, len, MOD9)) % MOD9};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {

        string s;
        cin >> s;
        int n = s.size();
        pll hash_left = {0, 0}, hash_right = {0, 0};

        ll ans = 0;
        for (int l = 0, r = n - 1, len = 0; l <= r; l++, r--, len++) {
            hash_left = add_right(hash_left, s[l], len);
            hash_right = add_left(hash_right, s[r]);
            if (hash_left == hash_right) {
                if (l == r) {
                    ans++;
                } else {
                    ans += 2;
                }
                len = -1;
                hash_left = {0, 0};
                hash_right = {0, 0};
            }
        }

        if (hash_left != make_pair(0LL, 0LL)) {
            ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}