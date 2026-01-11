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

    ll n, m;
    cin >> n >> m;
    vector<array<ll, 3>> xyc(m);
    for (ll i = 0; i < m; i++) {
        cin >> xyc[i][0] >> xyc[i][1] >> xyc[i][2];
        xyc[i][0]--;
        xyc[i][1]--;
    }

    vector<vector<pll>> adj(2e5 + 10);
    for (auto [x, y, c] : xyc) {
        adj[x].push_back({y, c});
    }

    vector<ll> dist(2e5 + 10, LLONG_MAX);
    dist[xyc[0][1]] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, xyc[0][1]});
    while (!pq.empty()) {
        auto [cost, v] = pq.top();
        pq.pop();
        if (dist[v] < cost)
            continue;
        for (auto [nv, nc] : adj[v]) {
            if (dist[nv] > dist[v] + nc) {
                dist[nv] = dist[v] + nc;
                pq.push({dist[nv], nv});
            }
        }
    }

    cout << (dist[xyc[0][0]] == LLONG_MAX ? -1 : dist[xyc[0][0]] + xyc[0][2]);

    return 0;
}