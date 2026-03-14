// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1), adj_inv(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u != v) {
            adj[u].push_back(v);
            adj_inv[v].push_back(u);
        }
    }

    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        sort(adj_inv[i].begin(), adj_inv[i].end());
        adj_inv[i].erase(unique(adj_inv[i].begin(), adj_inv[i].end()), adj_inv[i].end());
    }

    vector<int> min_in(n + 1, 1e9);
    for (int i = 1; i <= n; i++) {
        for (auto v : adj_inv[i]) {
            min_in[i] = min(min_in[i], v);
        }
    }

    // 1) solve reachability first
    // weight of (u -> v) = max(u, v)
    // use prim-ish algorithm
    vector<int> dist(n + 1, 1e9);
    dist[1] = 1;
    priority_queue<pii, vector<pii>, greater<>> pq;
    pq.push({1, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] != d) {
            continue;
        }
        for (auto v : adj[u]) {
            int w = max(u, v);
            if (dist[v] > max(d, w)) {
                dist[v] = max(d, w);
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> ans(n + 1);
    // +1 to min_in[u] <= i < u
    for (int u = 1; u <= n; u++) {
        if (min_in[u] > u || dist[u] == 1e9) {
            continue;
        }
        ans[min_in[u]]++;
        ans[u]--;
    }
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        if (dist[i] > i) {
            ans[i] = -1;
        }
        if (dist[i] == 1e9) {
            for (int j = i; j <= n; j++) {
                ans[j] = -1;
            }
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}