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

vector<vector<int>> combs(MOD + 1, vector<int>(MOD + 1, -1));

vector<ll> p_ary(ll n, ll p) {
    vector<ll> res;
    while (n) {
        res.push_back(n % p);
        n /= p;
    }
    return res;
}

void preprocess_combs() {
    for (ll n = 0; n <= MOD; n++) {
        combs[n][0] = 1;
        combs[n][n] = 1;
        for (ll k = 1; k < n; k++) {
            combs[n][k] = (combs[n - 1][k - 1] + combs[n - 1][k]) % MOD;
        }
    }
}

ll nck_mod_p(ll n, ll k, ll p) {
    ll res = 1;
    vector<ll> n_p = p_ary(n, p);
    vector<ll> k_p = p_ary(k, p);
    for (size_t i = 0; i < n_p.size(); i++) {
        ll ni = n_p[i];
        ll ki = (i < k_p.size()) ? k_p[i] : 0;
        if (ki > ni)
            return 0;
        res = (res * combs[ni][ki]) % p;
    }
    return res;
}

ll solve_without_obs(ll h, ll w) {
    if (h < 0 || w < 0)
        return 0;
    if ((h + w) % 3 != 0)
        return 0;
    ll moves = (h + w) / 3;
    ll diff = abs(h - w);
    if (diff < 0 || diff > moves)
        return 0;
    return nck_mod_p(moves, (diff + moves) / 2, MOD);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    preprocess_combs();

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        ll h, w, r;
        cin >> h >> w >> r;
        h--;
        w--;

        vector<pll> obs;
        for (ll i = 0; i < r; i++) {
            ll y, x;
            cin >> y >> x;
            y--;
            x--;
            obs.push_back({y, x});
        }
        sort(obs.begin(), obs.end());
        ll ans = solve_without_obs(h, w);
        for (int mask = 1; mask < (1 << r); mask++) {
            vector<int> idxs;
            for (int i = 0; i < r; i++) {
                if (mask & (1 << i)) {
                    idxs.push_back(i);
                }
            }
            ll ways = 1;
            ll prev_y = 0, prev_x = 0;
            for (int i : idxs) {
                ll oy = obs[i].first;
                ll ox = obs[i].second;
                ways = (ways * solve_without_obs(oy - prev_y, ox - prev_x)) % MOD;
                prev_y = oy;
                prev_x = ox;
            }
            ways = (ways * solve_without_obs(h - prev_y, w - prev_x)) % MOD;
            if (__builtin_popcount(mask) % 2 == 1) {
                ans = (ans - ways + MOD) % MOD;
            } else {
                ans = (ans + ways) % MOD;
            }
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }

    return 0;
}