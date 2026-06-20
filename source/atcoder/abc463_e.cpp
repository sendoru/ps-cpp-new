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

    ll n, m, y;
    cin >> n >> m >> y;
    vector<vector<array<ll, 2>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        ll s, e, t;
        cin >> s >> e >> t;
        adj[s].push_back({e, t});
        adj[e].push_back({s, t});
    }

    vector<ll> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        adj[0].push_back({i, x[i]});
        adj[i].push_back({0, x[i] + y});
    }

    vector<ll> dist(n + 1, 1e18);
    dist[1] = 0;
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] < d) {
            continue;
        }
        for (auto [u, t] : adj[v]) {
            if (dist[u] > dist[v] + t) {
                dist[u] = dist[v] + t;
                pq.push({dist[u], u});
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        cout << dist[i] << ' ';
    }

    return 0;
}