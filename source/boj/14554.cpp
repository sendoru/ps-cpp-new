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

    int n, m, s, e;
    cin >> n >> m >> s >> e;
    s--;
    e--;

    vector<vector<array<ll, 2>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<ll> dist(n, 1e18);
    vector<ll> cnt(n, 0);
    dist[s] = 0;
    cnt[s] = 1;
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] != d) {
            continue;
        }

        for (auto &[nv, w] : adj[v]) {
            if (dist[nv] > d + w) {
                dist[nv] = d + w;
                cnt[nv] = cnt[v];
                pq.push({dist[nv], nv});
            } else if (dist[nv] == d + w) {
                cnt[nv] += cnt[v];
                cnt[nv] %= MOD1 + 2;
            }
        }
    }

    cout << cnt[e] % (MOD1 + 2);

    return 0;
}