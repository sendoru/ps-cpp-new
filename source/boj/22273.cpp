// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll encode(vector<ll> &v) {
    ll res = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i]; j++) {
            res |= (1ll << (i * 8 + j));
        }
    }
    return res;
}

vector<ll> decode(ll x) {
    vector<ll> res(8);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (x & (1ll << (i * 8 + j))) {
                res[i]++;
            }
        }
    }
    return res;
}

vector<vector<ll>> get_comb_with_dup(ll n, ll k) {
    vector<vector<ll>> res;
    vector<ll> v(k);
    function<void(int, int)> dfs = [&](int idx, int start) {
        if (idx == k) {
            res.push_back(v);
            return;
        }
        for (int i = start; i <= n; i++) {
            v[idx] = i;
            dfs(idx + 1, i);
        }
    };
    dfs(0, 0);
    return res;
}

vector<ll> get_all_possible_encodes() {
    vector<ll> res;
    for (int i = 0; i <= 8; i++) {
        auto combs = get_comb_with_dup(8, i);
        for (auto &comb : combs) {
            vector<ll> v(8);
            for (auto &c : comb) {
                v[c]++;
            }
            res.push_back(encode(v));
        }
    }
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<ll> all_encodes = get_all_possible_encodes();
    unordered_map<ll, int> encodes_cnt, subset_encode_cnt;
    unordered_map<ll, vector<ll>> superset, subset;
    for (ll e1 : all_encodes) {
        if (__popcount<ll>(e1) >= 4) {
            for (ll e2 : all_encodes) {
                if ((e1 & e2) == e1) {
                    superset[e1].push_back(e2);
                }
            }
        } else {
            for (ll e2 : all_encodes) {
                if ((e1 & e2) == e1) {
                    subset[e2].push_back(e1);
                }
            }
        }
    }

    vector<ll> encodes = {0};
    int id = 1;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'C') {
            int r;
            cin >> r;
            vector<ll> v(8);
            for (int i = 0; i < r; i++) {
                int idx;
                cin >> idx;
                idx--;
                v[idx]++;
            }
            ll e = encode(v);
            encodes.push_back(e);
            encodes_cnt[e]++;
            for (ll subset_e : subset[e]) {
                subset_encode_cnt[subset_e]++;
            }
            id++;
        } else if (c == 'D') {
            int idx;
            cin >> idx;
            ll e = encodes[idx];
            encodes_cnt[e]--;
            for (ll subset_e : subset[e]) {
                subset_encode_cnt[subset_e]--;
            }
        } else {
            int r;
            cin >> r;
            vector<ll> v(8);
            for (int i = 0; i < r; i++) {
                int idx;
                cin >> idx;
                idx--;
                v[idx]++;
            }
            ll e = encode(v);
            int ans = 0;
            if (__popcount<ll>(e) >= 4) {
                for (ll superset_e : superset[e]) {
                    ans += encodes_cnt[superset_e];
                }
            } else {
                ans = subset_encode_cnt[e];
            }
            cout << ans << "\n";
        }
    }

    return 0;
}