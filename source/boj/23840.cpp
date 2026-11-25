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

vector<ll> dijk(const vector<vector<array<ll, 2>>> &adj, ll start) {
    ll n = adj.size();
    vector<ll> dist(n, 1e18);
    dist[start] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<array<ll, 2>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    ll x, z;
    cin >> x >> z;
    ll p;
    cin >> p;
    vector<ll> ys(p);
    for (int i = 0; i < p; i++) {
        cin >> ys[i];
    }

    auto x_dist = dijk(adj, x);
    auto z_dist = dijk(adj, z);
    vector<vector<ll>> y_dists;
    for (auto y : ys) {
        y_dists.push_back(dijk(adj, y));
    }

    vector<vector<ll>> dp((1 << p), vector<ll>(p, 1e18));
    for (int mask = 0; mask < (1 << p); mask++) {
        for (int i = 0; i < p; i++) {
            if (!(mask & (1 << i))) {
                continue;
            }
            if (mask == (1 << i)) {
                dp[mask][i] = x_dist[ys[i]];
            } else {
                for (int j = 0; j < p; j++) {
                    if (i == j || !(mask & (1 << j))) {
                        continue;
                    }
                    dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + y_dists[j][ys[i]]);
                }
            }
        }
    }

    ll ans = 1e18;
    for (int i = 0; i < p; i++) {
        ans = min(ans, dp[(1 << p) - 1][i] + z_dist[ys[i]]);
    }

    cout << (ans == 1e18 ? -1 : ans) << "\n";

    return 0;
}