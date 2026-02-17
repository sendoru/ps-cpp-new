// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MOD = 1e9 + 9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, x, y;
    cin >> n >> m >> x >> y;
    x--;
    y--;
    vector<vector<array<ll, 2>>> adj(n);
    for (int i = 0; i < m; i++) {
        ll s, e, w;
        cin >> s >> e >> w;
        s--;
        e--;
        adj[s].push_back({e, w});
    }

    vector<array<ll, 2>> dists(n, {(ll)1e18, (ll)1e18});
    vector<ll> cnt(n);
    dists[x] = {0, 0};
    cnt[x] = 1;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, 0, x});
    while (!pq.empty()) {
        auto [dist, edge_cnt, u] = pq.top();
        pq.pop();
        if (dist > dists[u][0] || (dist == dists[u][0] && edge_cnt > dists[u][1])) {
            continue;
        }
        for (auto [v, w] : adj[u]) {
            ll ndist = dist + w;
            ll nedge_cnt = edge_cnt + 1;
            if (ndist < dists[v][0] || (ndist == dists[v][0] && nedge_cnt < dists[v][1])) {
                dists[v] = {ndist, nedge_cnt};
                cnt[v] = cnt[u];
                pq.push({dists[v][0], dists[v][1], v});
            } else if (ndist == dists[v][0] && nedge_cnt == dists[v][1]) {
                cnt[v] += cnt[u];
                cnt[v] %= MOD;
            }
        }
    }

    if (dists[y][0] == 1e18) {
        cout << "-1";
    } else {
        cout << dists[y][0] << '\n'
             << dists[y][1] << '\n'
             << cnt[y];
    }

    return 0;
}