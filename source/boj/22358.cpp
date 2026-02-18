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

    ll n, m, k, s, t;
    cin >> n >> m >> k >> s >> t;
    s--;
    t--;
    vector<vector<array<ll, 2>>> adj(n), adj_inv(n);
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj_inv[v].push_back({u, w});
    }

    vector<vector<ll>> dp(n, vector<ll>(k + 1, -1));
    vector<vector<ll>> indeg(n, vector<ll>(k + 1));
    for (int here = 0; here < n; here++) {
        for (auto [there, w] : adj[here]) {
            for (int i = 0; i <= k; i++) {
                indeg[there][i]++;
            }
        }
    }

    for (auto here = 0; here < n; here++) {
        for (auto [there, w] : adj_inv[here]) {
            for (int i = 0; i < k; i++) {
                indeg[there][i + 1]++;
            }
        }
    }

    // remove unneeded edges
    queue<array<ll, 2>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (indeg[i][j] == 0 && !(i == s && j == 0)) {
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto [here, used] = q.front();
        q.pop();
        for (auto [there, w] : adj[here]) {
            indeg[there][used]--;
            if (indeg[there][used] == 0 && !(there == s && used == 0)) {
                q.push({there, used});
            }
        }
        if (used == k) {
            continue;
        }
        for (auto [there, w] : adj_inv[here]) {
            indeg[there][used + 1]--;
            if (indeg[there][used + 1] == 0) {
                q.push({there, used + 1});
            }
        }
    }

    dp[s][0] = 0;
    q.push({s, 0});

    while (!q.empty()) {
        auto [here, used] = q.front();
        q.pop();
        for (auto [there, w] : adj[here]) {
            dp[there][used] = max(dp[there][used], dp[here][used] + w);
            indeg[there][used]--;
            if (indeg[there][used] == 0) {
                q.push({there, used});
            }
        }
        if (used == k) {
            continue;
        }
        for (auto [there, w] : adj_inv[here]) {
            dp[there][used + 1] = max(dp[there][used + 1], dp[here][used]);
            indeg[there][used + 1]--;
            if (indeg[there][used + 1] == 0) {
                q.push({there, used + 1});
            }
        }
    }

    ll ans = -1;
    for (int i = 0; i <= k; i++) {
        ans = max(ans, dp[t][i]);
    }
    cout << ans;

    return 0;
}