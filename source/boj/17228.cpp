// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Hash {
    ll h1, h2, len;
    // class variable
    static const ll base1 = 131, base2 = 137;
    static const ll mod1 = MOD9, mod2 = MOD1;
    static vector<ll> pow1, pow2;
    static void init_pow() {
        if (!pow1.empty())
            return;
        pow1.push_back(1);
        pow2.push_back(1);
        for (int i = 1; i <= 600000; i++) {
            pow1.push_back((pow1.back() * base1) % mod1);
            pow2.push_back((pow2.back() * base2) % mod2);
        }
    }
    Hash() : h1(0), h2(0), len(0) { init_pow(); }
    Hash(char c) : h1(c), h2(c), len(1) { init_pow(); }
    Hash(const string &s) {
        init_pow();
        h1 = 0, h2 = 0, len = s.size();
        for (char c : s) {
            h1 = (h1 * base1 + c) % mod1;
            h2 = (h2 * base2 + c) % mod2;
        }
    }
    void push_back(char c) {
        h1 = (h1 * base1 + c) % mod1;
        h2 = (h2 * base2 + c) % mod2;
        len++;
    }
    void pop_front(char c) {
        h1 = (h1 - c * pow1[len - 1] % mod1 + mod1) % mod1;
        h2 = (h2 - c * pow2[len - 1] % mod2 + mod2) % mod2;
        len--;
    }
    bool operator==(const Hash &other) const {
        return h1 == other.h1 && h2 == other.h2 && len == other.len;
    }
};

vector<ll> Hash::pow1;
vector<ll> Hash::pow2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> par(n);
    vector<vector<int>> adj(n);
    vector<char> chars(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        par[v] = u;
        adj[u].push_back(v);
        char c;
        cin >> c;
        chars[v] = c;
    }
    string p;
    cin >> p;
    int l = p.size();

    vector<Hash> path_hash(n);
    vector<int> dfs_stack;
    function<void(int)> dfs = [&](int u) {
        dfs_stack.push_back(u);
        for (int v : adj[u]) {
            path_hash[v] = path_hash[u];
            path_hash[v].push_back(chars[v]);
            if (dfs_stack.size() > l) {
                path_hash[v].pop_front(chars[dfs_stack[dfs_stack.size() - l]]);
            }
            dfs(v);
        }
        dfs_stack.pop_back();
    };

    dfs(0);
    Hash p_hash(p);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (path_hash[i] == p_hash) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}