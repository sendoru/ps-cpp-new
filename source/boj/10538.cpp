// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll HASH_BASE = 37;
const ll HASH_MOD = 1e9 + 7;
ll HASH_MOD_INV;
map<pll, ll> HASH_MOD_INV_MAP;

ll mod_pow(ll b, ll e, ll m = MOD1) {
    ll ret = 1;
    while (e) {
        if (e & 1) {
            ret = (ret * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return ret;
}

ll mod_inv(ll a, ll m = MOD1) {
    if (HASH_MOD_INV_MAP.count({a, m})) {
        return HASH_MOD_INV_MAP[{a, m}];
    }
    return HASH_MOD_INV_MAP[{a, m}] = mod_pow(a, m - 2, m);
}

template <typename T>
ll hash_push_back(ll h, T c, ll len, ll hash_base = HASH_BASE, ll hash_mod = HASH_MOD) {
    return (h + c * mod_pow(hash_base, len, hash_mod)) % hash_mod;
}

template <typename T>
ll hash_pop_front(ll h, T c, ll len, ll hash_base = HASH_BASE, ll hash_mod = HASH_MOD) {
    return (h - c + hash_mod) * mod_inv(hash_base, hash_mod) % hash_mod;
}

template <typename T>
ll get_hash(T s, ll hash_base = HASH_BASE, ll hash_mod = HASH_MOD) {
    ll h = 0;
    for (int i = 0; i < s.size(); i++) {
        h = hash_push_back(h, s[i], i, hash_base, hash_mod);
    }
    return h;
}

template <typename T>
vector<int> get_failure(T s) {
    int n = s.size();
    vector<int> f(n);
    for (int i = 1; i < n; i++) {
        int j = f[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = f[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        f[i] = j;
    }
    return f;
}

template <typename T>
vector<int> kmp(T s, T p) {
    int n = s.size();
    int m = p.size();
    vector<int> f = get_failure(p);
    vector<int> ret;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) {
            j = f[j - 1];
        }
        if (s[i] == p[j]) {
            j++;
        }
        if (j == m) {
            ret.push_back(i - m + 1);
            j = f[j - 1];
        }
    }
    return ret;
}

vector<vector<bool>> get_match(vector<string> &p, vector<string> &m, ll hash_base, ll hash_mod) {
    int hp = p.size();
    int wp = p[0].size();
    int hm = m.size();
    int wm = m[0].size();

    vector<ll> p_hash(hp);
    vector<vector<ll>> m_hash(hm, vector<ll>(wm - wp + 1));

    for (int i = 0; i < hp; i++) {
        p_hash[i] = get_hash(p[i], hash_base, hash_mod);
    }

    for (int i = 0; i < hm; i++) {
        for (int j = 0; j < wp; j++) {
            m_hash[i][0] = hash_push_back(m_hash[i][0], m[i][j], j, hash_base, hash_mod);
        }
        for (int j = 1; j <= wm - wp; j++) {
            m_hash[i][j] = hash_push_back(m_hash[i][j - 1], m[i][j + wp - 1], wp, hash_base, hash_mod);
            m_hash[i][j] = hash_pop_front(m_hash[i][j], m[i][j - 1], wp + 1, hash_base, hash_mod);
        }
    }

    auto p_failure = get_failure(p[0]);
    vector<vector<bool>> ret(hm - hp + 1, vector<bool>(wm - wp + 1, false));
    for (int j = 0; j <= wm - wp; j++) {
        vector<ll> col_hash(hm);
        for (int i = 0; i < hm; i++) {
            col_hash[i] = m_hash[i][j];
        }

        vector<int> match = kmp(col_hash, p_hash);
        for (auto idx : match) {
            ret[idx][j] = true;
        }
    }

    return ret;
}

int main() {
    HASH_MOD_INV = mod_inv(HASH_BASE);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int hp, wp, hm, wm;
    cin >> hp >> wp >> hm >> wm;

    vector<string> p(hp);
    vector<string> m(hm);

    for (int i = 0; i < hp; i++) {
        cin >> p[i];
        for (int j = 0; j < wp; j++) {
            if (p[i][j] == 'x') {
                p[i][j] = 0;
            } else {
                p[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < hm; i++) {
        cin >> m[i];
        for (int j = 0; j < wm; j++) {
            if (m[i][j] == 'x') {
                m[i][j] = 0;
            } else {
                m[i][j] = 1;
            }
        }
    }

    vector<vector<bool>> match(hm - hp + 1, vector<bool>(wm - wp + 1, true));
    vector<ll> hashes = {37, 8183};
    vector<ll> mods = {998244353};
    for (auto hash : hashes) {
        for (auto mod : mods) {
            auto new_match = get_match(p, m, hash, mod);
            for (int i = 0; i <= hm - hp; i++) {
                for (int j = 0; j <= wm - wp; j++) {
                    match[i][j] = match[i][j] && new_match[i][j];
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i <= hm - hp; i++) {
        for (int j = 0; j <= wm - wp; j++) {
            if (match[i][j]) {
                ans++;
            }
        }
    }
    cout << ans << '\n';

    return 0;
}