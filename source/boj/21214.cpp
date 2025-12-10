// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll count_divisors(ll x) {
    ll cnt = 0;
    for (ll i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            cnt++;
            if (i * i != x) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<ll> f(n);
    for (int i = 0; i < n; i++) {
        f[i] = (i + count_divisors(i)) % n;
    }

    // chain_len[i] := minimum n s.t. {f^0, f^1, ..., f^n} contains duplicate
    vector<ll> chain_len(n, -1);
    for (int i = 0; i < n; i++) {
        if (chain_len[i] != -1) {
            continue;
        }
        unordered_map<ll, ll> mp;
        ll cur = i;
        ll step = 0;
        while (mp.find(cur) == mp.end() && chain_len[cur] == -1) {
            mp[cur] = step;
            cur = f[cur];
            step++;
        }
        ll cycle_start = -1;
        ll cycle_len = -1;
        if (chain_len[cur] != -1) {
            cycle_start = step;
            cycle_len = chain_len[cur];
        } else {
            cycle_start = mp[cur];
            cycle_len = step - cycle_start;
        }
        for (auto &[key, val] : mp) {
            if (val < cycle_start) {
                chain_len[key] = cycle_len + (cycle_start - val);
            } else {
                chain_len[key] = cycle_len;
            }
        }
    }

    // g_n(x) = f^n(x)
    vector<vector<ll>> g(20, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        g[0][i] = f[i];
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n; i++) {
            g[j][i] = g[j - 1][g[j - 1][i]];
        }
    }

    // h_n(x) = f^0(x) + f^1(x) + ... + f^(n-1)(x)
    vector<vector<ll>> h(20, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        h[0][i] = i;
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n; i++) {
            h[j][i] = h[j - 1][i] + h[j - 1][g[j - 1][i]];
        }
    }

    ll min_sum = 1e18, min_pos = -1;
    for (int i = 0; i < n; i++) {
        if (chain_len[i] >= k) {
            ll cur_sum = 0;
            ll cur_pos = i;
            ll rem = k;
            for (int j = 19; j >= 0; j--) {
                if ((rem >> j) & 1) {
                    cur_sum += h[j][cur_pos];
                    cur_pos = g[j][cur_pos];
                    rem ^= (1 << j);
                }
            }
            if (cur_sum < min_sum) {
                min_sum = cur_sum;
                min_pos = i;
            }
        }
    }

    if (min_pos == -1) {
        cout << -1;
    } else {
        vector<ll> ans;
        for (int i = 0; i < k; i++) {
            ans.push_back(min_pos);
            min_pos = f[min_pos];
        }
        for (int i = 0; i < k; i++) {
            cout << ans[i] << ' ';
        }
    }

    return 0;
}