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

    ll n, m, p;
    cin >> n >> m >> p;
    vector<vector<array<ll, 3>>> adj(n);
    for (int i = 0; i < m; i++) {
        ll u, v, w, a;
        cin >> u >> v >> w >> a;
        u--;
        v--;
        adj[u].push_back({v, w, a});
        adj[v].push_back({u, w, a});
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;
    vector<array<ll, 2>> dist(n, {(ll)2e18, (ll)2e18});
    dist[0] = {0, 0};
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        auto [cnt, remain, u] = pq.top();
        pq.pop();
        if (make_pair(cnt, remain) > make_pair(dist[u][0], dist[u][1])) {
            continue;
        }
        for (auto [v, w, a] : adj[u]) {
            ll new_cnt, new_remain;
            if (a == 1) {
                new_cnt = cnt + (remain + w) / p;
                new_remain = (remain + w) % p;
                if (new_remain == 0) {
                    new_cnt--;
                    new_remain = p;
                }
            } else {
                if (remain + w <= p) {
                    new_cnt = cnt;
                    new_remain = remain + w;
                } else if (w <= p) {
                    new_cnt = cnt + 1;
                    new_remain = w;
                } else {
                    continue;
                }
            }
            if (make_pair(new_cnt, new_remain) < make_pair(dist[v][0], dist[v][1])) {
                dist[v] = {new_cnt, new_remain};
                pq.push({new_cnt, new_remain, v});
            }
        }
    }

    ll ans = dist.back()[0];
    if (ans == (ll)2e18) {
        cout << "But I dont have 30k" << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}