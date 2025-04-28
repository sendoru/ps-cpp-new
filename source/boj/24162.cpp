// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll dot(pll a, pll b, pll c) {
    ll abx = b.first - a.first;
    ll aby = b.second - a.second;

    ll bcx = c.first - b.first;
    ll bcy = c.second - b.second;

    return abx * bcx + aby * bcy;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pll> dots(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> dots[i].first >> dots[i].second;
    }

    vector<vector<pll>> adj(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    // dist[cur][pre] = cost
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, LLONG_MAX));

    dist[1][0] = 0;
    // cost, pre, cur
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;
    pq.push({0, 0, 1});
    while (!pq.empty()) {
        auto [cost, pre, cur] = pq.top();
        pq.pop();

        if (dist[cur][pre] < cost)
            continue;
        for (auto &[next, edge_cost] : adj[cur]) {
            if (pre != 0 && dot(dots[pre], dots[cur], dots[next]) < 0) {
                continue;
            }
            ll new_cost = cost + edge_cost;
            if (dist[next][cur] > new_cost) {
                dist[next][cur] = new_cost;
                pq.push({new_cost, cur, next});
            }
        }
    }

    ll ans = *min_element(dist[2].begin(), dist[2].end());
    if (ans == LLONG_MAX) {
        ans = -1;
    }

    cout << ans << '\n';

    return 0;
}