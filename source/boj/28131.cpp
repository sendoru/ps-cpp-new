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

    ll n, m, k;
    cin >> n >> m >> k;
    ll s, t;
    cin >> s >> t;
    s--;
    t--;
    vector<vector<array<ll, 2>>> adj(n);
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
    }

    vector<vector<ll>> dist(n, vector<ll>(k, 1e18));
    dist[s][0] = 0;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, s, 0});
    while (!pq.empty()) {
        auto [d, u, r] = pq.top();
        pq.pop();
        if (dist[u][r] < d) {
            continue;
        }
        for (auto [v, w] : adj[u]) {
            ll nr = (r + w) % k;
            if (dist[v][nr] > d + w) {
                dist[v][nr] = d + w;
                pq.push({dist[v][nr], v, nr});
            }
        }
    };

    if (dist[t][0] == 1e18) {
        cout << "IMPOSSIBLE";
    } else {
        cout << dist[t][0];
    }
    return 0;
}