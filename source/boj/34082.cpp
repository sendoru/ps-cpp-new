// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pll> dp(n);
    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        dp[u] = {0, 0};
        vector<ll> s;
        vector<int> childs;
        for (int v : adj[u]) {
            if (visited[v]) {
                continue;
            }
            dfs(v);
            childs.push_back(v);
            s.push_back((dp[v].first + dp[v].second + 1) % m);
        }

        if (s.empty()) {
            return;
        }

        dp[u].first = 1;
        for (auto elem : s) {
            dp[u].first = dp[u].first * elem % m;
        }
        dp[u].first = (dp[u].first + m - 1) % m;

        vector<ll> pf_prod(s.size(), 1);
        pf_prod[0] = s[0];
        for (int i = 1; i < s.size(); i++) {
            pf_prod[i] = pf_prod[i - 1] * s[i] % m;
        }
        vector<ll> sf_prod(s.size(), 1);
        sf_prod[s.size() - 1] = s[s.size() - 1];
        for (int i = s.size() - 2; i >= 0; i--) {
            sf_prod[i] = sf_prod[i + 1] * s[i] % m;
        }
        for (int i = 0; i < s.size(); i++) {
            ll cur = 1;
            if (i != 0) {
                cur = (cur * pf_prod[i - 1]) % m;
            }
            if (i != s.size() - 1) {
                cur = (cur * sf_prod[i + 1]) % m;
            }
            cur = (cur * (dp[childs[i]].first + 1)) % m;
            dp[u].second = (dp[u].second + cur) % m;
        }
    };

    dfs(0);
    ll ans = modpow(2, n - 1, m);
    ans = (ans - dp[0].first - dp[0].second - 1 + 3 * m) % m;
    cout << (2 * ans) % m;

    return 0;
}