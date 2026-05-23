// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> facts;
vector<ll> inv_facts;

ll modpow(ll b, ll e, ll m) {
    b %= m;
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

void preprocess_facts() {
    facts.resize((int)1e6 + 10);
    inv_facts.resize((int)1e6 + 10);
    facts[0] = 1;
    for (int i = 1; i < facts.size(); i++) {
        facts[i] = facts[i - 1] * i % MOD9;
    }
    inv_facts.back() = modpow(facts.back(), MOD9 - 2, MOD9);
    for (int i = (int)inv_facts.size() - 2; i >= 0; i--) {
        inv_facts[i] = inv_facts[i + 1] * (i + 1) % MOD9;
    }
}

ll comb(ll n, ll r) {
    if (r > n || r < 0 || n < 0) {
        return 0;
    }
    // return facts[n] * inv_facts[r] % MOD9 * inv_facts[n - r] % MOD9;
    // need to use naive approach instead
    // since n is up to 1e9 but sum of r is up to 1e6

    ll res = 1;
    for (ll i = 0; i < r; i++) {
        res = res * ((n - i) % MOD9) % MOD9;
        res = res * modpow(i + 1, MOD9 - 2, MOD9) % MOD9;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    preprocess_facts();

    int n;
    cin >> n;
    vector<int> p(n);
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        adj[p[i]].push_back(i);
    }

    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<ll> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    vector<ll> subtree_c_sum(n), subtree_d_sum(n);
    vector<ll> dp(n, 1);
    function<ll(int)> dfs = [&](int u) {
        subtree_c_sum[u] = c[u];
        subtree_d_sum[u] = d[u];
        dp[u] = 1;
        for (int v : adj[u]) {
            dfs(v);
            subtree_c_sum[u] += subtree_c_sum[v];
            subtree_d_sum[u] += subtree_d_sum[v];
            dp[u] = dp[u] * dp[v] % MOD9;
        }
        ll cands_cnt = subtree_c_sum[u] - subtree_d_sum[u] + d[u];
        dp[u] = dp[u] * comb(cands_cnt, d[u]) % MOD9;
        return dp[u];
    };

    cout << dfs(0) << "\n";

    return 0;
}