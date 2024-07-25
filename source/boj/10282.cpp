#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> dijkstra(vector<vector<pll>> &adj, int start) {
    vector<ll> dist(adj.size(), 1e18);
    dist[start] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d) {
            continue;
        }
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, d, c;
        cin >> n >> d >> c;
        vector<vector<pll>> adj(n + 1);
        for (int i = 0; i < d; i++) {
            int a, b, s;
            cin >> a >> b >> s;
            adj[b].push_back({a, s});
        }

        auto dist = dijkstra(adj, c);
        pll ans = {0, -1};
        for (int i = 1; i <= n; i++) {
            if (dist[i] < 1e18) {
                ans.first++;
                ans.second = max(ans.second, dist[i]);
            }
        }

        cout << ans.first << " " << ans.second << "\n";
    }

    return 0;
}