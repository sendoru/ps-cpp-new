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
    while (e > 0) {
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

    string s, t;
    cin >> s >> t;
    ll n = s.length(), m = t.length();

    vector<vector<ll>> next_pos(n + 1, vector<ll>(26, -1));
    for (int i = n - 1; i >= 0; i--) {
        next_pos[i] = next_pos[i + 1];
        next_pos[i][s[i] - 'a'] = i;
    }

    ll ans = n * (n + 1) / 2;
    for (int i = 0; i < n; i++) {
        ll cur_pos = i;
        bool ok = true;
        for (auto c : t) {
            if (next_pos[cur_pos][c - 'a'] == -1) {
                ok = false;
                break;
            }
            cur_pos = next_pos[cur_pos][c - 'a'] + 1;
        }
        if (ok) {
            ans -= n - cur_pos + 1;
        }
    }

    cout << ans;

    return 0;
}