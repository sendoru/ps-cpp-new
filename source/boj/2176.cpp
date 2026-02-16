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

    int s = 0, t = 1;
    int n, m;
    cin >> n >> m;
    vector<vector<pll>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<ll> dists(n, 1e18);
    dists[t] = 0;
    priority_queue<pll, vector<pll>, greater<>> pq;
    pq.push({0, t});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dists[v] != d) {
            continue;
        }
        for (auto &[nv, w] : adj[v]) {
            if (dists[nv] > d + w) {
                dists[nv] = d + w;
                pq.push({dists[nv], nv});
            }
        }
    }

    vector<vector<int>> adj_new(n);
    vector<int> indeg(n);
    for (int v = 0; v < n; v++) {
        for (auto &[nv, w] : adj[v]) {
            if (dists[nv] < dists[v]) {
                adj_new[v].push_back(nv);
                indeg[nv]++;
            }
        }
    }

    vector<ll> dp(n, 0);
    dp[0] = 1;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int nv : adj_new[v]) {
            dp[nv] += dp[v];
            indeg[nv]--;
            if (indeg[nv] == 0) {
                q.push(nv);
            }
        }
    }

    cout << dp[t];

    return 0;
}