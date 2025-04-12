// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        adj[s].push_back(e);
        adj[e].push_back(s);
    }

    vector<int> dist(n, 1e8);
    dist[0] = 0;
    // the dist is defined as prim-like
    // more precise, the dist between 0-v is
    // the minimum greatest number of vertices
    // in the path from 0 to v

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d > dist[v]) {
            continue;
        }
        for (auto u : adj[v]) {
            if (dist[u] > max(u, d)) {
                dist[u] = max(u, d);
                pq.push({dist[u], u});
            }
        }
    }

    set<int> nodes;
    vector<int> ans(n, -1);
    int max_dist = 0;
    for (int i = 0; i < n; i++) {
        for (auto nxt : adj[i]) {
            if (nxt > i) {
                nodes.insert(nxt);
            }
        }
        nodes.erase(i);
        max_dist = max(max_dist, dist[i]);
        if (max_dist <= i) {
            ans[i] = nodes.size();
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}