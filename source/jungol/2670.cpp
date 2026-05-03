// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int adj[2'020'010];

ll modpow(ll b, ll e) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = res * b % MOD1;
        }
        b = b * b % MOD1;
        e >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, r;
    cin >> n >> r;
    vector<int> f(n);
    for (int s = 0; s < n; s++) {
        cin >> f[s];
        f[s]--;
    }

    vector<int> deg_pf_sum(n + 1);
    for (int i = 0; i < n; i++) {
        if (f[i] == i) {
            continue;
        }
        if (f[i] < i && f[f[i]] == i) {
            continue;
        }
        deg_pf_sum[i + 1]++;
        deg_pf_sum[f[i] + 1]++;
    }

    for (int i = 1; i <= n; i++) {
        deg_pf_sum[i] += deg_pf_sum[i - 1];
    }
    vector<int> adj_idx(n);

    for (int i = 0; i < n; i++) {
        if (f[i] == i) {
            continue;
        }
        if (f[i] < i && f[f[i]] == i) {
            continue;
        }
        adj[adj_idx[i] + deg_pf_sum[i]] = f[i];
        adj_idx[i]++;
        adj[adj_idx[f[i]] + deg_pf_sum[f[i]]] = i;
        adj_idx[f[i]]++;
    }

    adj_idx.clear();
    f.clear();

    vector<int> dp(n + 10);
    dp[3] = r * (r - 1) % MOD1;
    ll cur = r * (r - 1) % MOD1;
    for (int i = 4; i <= n; i++) {
        cur = cur * (r - 1) % MOD1;
        dp[i] = (cur - dp[i - 1] + MOD1) % MOD1;
    }

    // all components are trees or have exactly one cycle
    ll ans = 1;
    vector<bool> visited(n);
    for (int node = 0; node < n; node++) {
        if (visited[node]) {
            continue;
        }
        bool has_cycle = false;
        pair<int, int> cycle_nodes = {-1, -1};
        int size = 0;
        vector<int> visited_nodes;
        queue<pii> q;
        q.push({node, -1});
        visited[node] = true;
        while (!q.empty()) {
            auto [u, p] = q.front();
            q.pop();
            size++;
            visited_nodes.push_back(u);
            for (int i = deg_pf_sum[u]; i < deg_pf_sum[u + 1]; i++) {
                int v = adj[i];
                if (v == p) {
                    continue;
                }
                if (visited[v]) {
                    has_cycle = true;
                    cycle_nodes = {u, v};
                    continue;
                }
                visited[v] = true;
                q.push({v, u});
            }
        }
        if (has_cycle) {
            int cycle_size = 0;
            for (int u : visited_nodes) {
                visited[u] = false;
            }
            q.push({cycle_nodes.first, 0});
            visited[cycle_nodes.first] = true;
            while (!q.empty()) {
                auto [u, dist] = q.front();
                q.pop();
                if (u == cycle_nodes.second) {
                    cycle_size = dist + 1;
                    // do not break; we need to mark all nodes in the comopnent as visited
                }
                for (int i = deg_pf_sum[u]; i < deg_pf_sum[u + 1]; i++) {
                    int v = adj[i];
                    if (visited[v] || (v == cycle_nodes.second && dist == 0)) {
                        continue;
                    }
                    visited[v] = true;
                    q.push({v, dist + 1});
                }
            }
            if (cycle_size == 0) {
                // self loop
                cout << "Error";
                return 0;
            }
            ll cycle_contrib = r * modpow(r - 1, cycle_size - 1) % MOD1;
            cycle_contrib = (cycle_contrib - dp[cycle_size] + MOD1) % MOD1;
            ans = ans * cycle_contrib % MOD1;
            ans = ans * modpow(r - 1, size - cycle_size) % MOD1;
        } else {
            ans = ans * r % MOD1;
            ans = ans * modpow(r - 1, size - 1) % MOD1;
        }
    }

    cout << ans;

    return 0;
}