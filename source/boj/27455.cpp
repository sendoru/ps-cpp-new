// #include "atcoder/all"
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> dijk(vector<vector<pll>> &adj, vector<int> &l, int s, int th) {
    int v = adj.size();
    vector<ll> dist(v, 1e18);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [cur_d, u] = pq.top();
        pq.pop();
        if (cur_d > dist[u])
            continue;
        for (auto [v, w] : adj[u]) {
            if (l[v] <= th && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, v, e;
    cin >> n >> v >> e;
    vector<int> l(v);
    for (int i = 0; i < v; i++) {
        cin >> l[i];
    }
    vector<int> k(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        k[i]--;
    }
    vector<int> k_inv(v, -1);
    for (int i = 0; i < n; i++) {
        k_inv[k[i]] = i;
    }

    vector<vector<pll>> adj(v);
    for (int i = 0; i < e; i++) {
        ll cur, nxt, w;
        cin >> cur >> nxt >> w;
        cur--;
        nxt--;
        adj[cur].emplace_back(nxt, w);
    }

    // starts from k[i], th = j
    vector<vector<vector<ll>>> dists(n + 1, vector<vector<ll>>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (l[k[i]] > j) {
                dists[i][j] = vector<ll>(n, 1e18);
            }
            auto all_dist = dijk(adj, l, k[i], j);
            dists[i][j] = vector<ll>(n);
            for (auto v : k) {
                dists[i][j][k_inv[v]] = all_dist[v];
            }
        }
    }

    // i == n reserved for start from s
    dists[n] = vector<vector<ll>>(n);
    for (int j = 0; j < n; j++) {
        auto all_dist = dijk(adj, l, 0, j);
        dists[n][j] = vector<ll>(n);
        for (auto v : k) {
            dists[n][j][k_inv[v]] = all_dist[v];
        }
    }

    // visited bitmask, last visited
    vector<vector<ll>> dp(1 << n, vector<ll>(n, 1e18));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = dists[n][0][i];
    }
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)))
                continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v))
                    continue;
                int th = __builtin_popcount(mask);
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v],
                                             dp[mask][u] + dists[u][th][v]);
            }
        }
    }

    ll ans = 1e18;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[(1 << n) - 1][i]);
    }
    if (ans == 1e18) {
        cout << -1;
    } else {
        cout << ans;
    }

    return 0;
}