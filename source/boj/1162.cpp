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

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pll>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<vector<ll>> dist(n, vector<ll>(k + 1, -1));
    dist[0][0] = 0;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        auto [d, v, c] = pq.top();
        pq.pop();
        if (dist[v][c] != d) {
            continue;
        }

        for (auto &[nv, w] : adj[v]) {
            if (dist[nv][c] == -1 || dist[nv][c] > d + w) {
                dist[nv][c] = d + w;
                pq.push({dist[nv][c], nv, c});
            }
            if (c < k && (dist[nv][c + 1] == -1 || dist[nv][c + 1] > d)) {
                dist[nv][c + 1] = d;
                pq.push({dist[nv][c + 1], nv, c + 1});
            }
        }
    }

    cout << *min_element(dist[n - 1].begin(), dist[n - 1].end());

    return 0;
}