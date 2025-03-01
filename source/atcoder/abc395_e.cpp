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

    ll n, m, x;
    cin >> n >> m >> x;

    vector<vector<ll>> adj_list(n);
    vector<vector<ll>> adj_list_rev(n);
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        adj_list[a].push_back(b);
        adj_list_rev[b].push_back(a);
    }

    vector<vector<ll>> dist(n, {LLONG_MAX, LLONG_MAX});
    dist[0][0] = 0;

    // {c, n, 0} c: cost, n: node, 0 means on original graph
    // {c, n, 1} c: cost, n: node, 1 means on reversed graph
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto top = pq.top();
        ll cost = top[0];
        ll node = top[1];
        ll is_rev = top[2];
        pq.pop();

        if (dist[node][is_rev] < cost) {
            continue;
        }

        // filp edge
        ll next_cost = cost + x;
        ll next_is_rev = 1 - is_rev;
        if (next_cost < dist[node][next_is_rev]) {
            dist[node][next_is_rev] = next_cost;
            pq.push({next_cost, node, next_is_rev});
        }

        // travel on this graph
        for (auto next : (is_rev ? adj_list_rev[node] : adj_list[node])) {
            if (cost + 1 < dist[next][is_rev]) {
                dist[next][is_rev] = cost + 1;
                pq.push({cost + 1, next, is_rev});
            }
        }
    }

    cout << min(dist[n - 1][0], dist[n - 1][1]) << '\n';

    return 0;
}