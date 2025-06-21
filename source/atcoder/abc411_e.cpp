#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll ret = 1;
    while (e > 0) {
        if (e & 1) {
            ret = (ret * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return ret;
}

ll inv6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    inv6 = modpow(6, MOD9 - 2, MOD9);

    int n;
    cin >> n;
    vector<vector<ll>> dice(n, vector<ll>(6));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            cin >> dice[i][j];
        }
    }

    // 좌표압축
    vector<ll> unique_vals;
    for (const auto &die : dice) {
        for (ll value : die) {
            unique_vals.push_back(value);
        }
    }

    sort(unique_vals.begin(), unique_vals.end());
    unique_vals.erase(unique(unique_vals.begin(), unique_vals.end()), unique_vals.end());

    map<ll, int> value_to_index;
    int index = 0;
    for (ll value : unique_vals) {
        value_to_index[value] = index++;
    }

    vector<vector<ll>> comp_dice(n, vector<ll>(6));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            comp_dice[i][j] = value_to_index[dice[i][j]];
        }
    }

    ll prev_val = 0;
    vector<ll> cnts(n);
    ll zeros = n;
    bool num_built = false;
    ll num = 0;
    ll ans = 0;

    map<ll, vector<int>> by_val;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            ll val = dice[i][j];
            by_val[val].push_back(i);
        }
    }

    for (ll val : unique_vals) {
        ll diff = val - prev_val;
        ll add;
        if (zeros > 0) {
            add = diff;
        } else {
            ll p_le = num * modpow(inv6, n, MOD9) % MOD9;
            add = diff * (1 - p_le + MOD9) % MOD9;
        }
        ans = (ans + add) % MOD9;

        for (int idx : by_val[val]) {
            if (cnts[idx] == 0) {
                zeros--;
            }
            cnts[idx]++;
            if (num_built) {
                num = num * cnts[idx] % MOD9;
                num = num * modpow(cnts[idx] - 1, MOD9 - 2, MOD9) % MOD9;
            }
        }

        if (zeros == 0 && !num_built) {
            num_built = true;
            num = 1;
            for (int i = 0; i < n; i++) {
                num = num * cnts[i] % MOD9;
            }
        }

        prev_val = val;
    }

    cout << ans << "\n";
}