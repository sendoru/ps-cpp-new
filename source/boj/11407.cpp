// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pair<ll, ll> mcmf(vector<vector<ll>> &cap, vector<vector<ll>> &cost, int s, int t) {
    int n = cap.size();

    ll flow_total = 0, cost_total = 0;
    vector<vector<ll>> flow(n, vector<ll>(n, 0));

    while (true) {
        vector<ll> dist(n, 1e15);
        vector<int> parent(n, -1);
        vector<bool> in_queue(n, false);
        queue<int> q;

        dist[s] = 0;
        q.push(s);
        in_queue[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;
            for (int v = 0; v < n; v++) {
                if (cap[u][v] > flow[u][v] && dist[v] > dist[u] + cost[u][v]) {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                    if (!in_queue[v]) {
                        q.push(v);
                        in_queue[v] = true;
                    }
                }
            }
        }

        if (dist[t] >= 1e15)
            break;

        ll f = 1e15;
        for (int v = t; v != s; v = parent[v]) {
            f = min(f, cap[parent[v]][v] - flow[parent[v]][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            flow[parent[v]][v] += f;
            flow[v][parent[v]] -= f;
            cost_total += f * cost[parent[v]][v];
        }

        flow_total += f;
    }

    return {flow_total, cost_total};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int node_cnt = n + m + 2;

    vector<vector<ll>> cap(node_cnt, vector<ll>(node_cnt, 0));
    vector<vector<ll>> cost(node_cnt, vector<ll>(node_cnt, 0));

    for (int node = m + 1; node < node_cnt - 1; node++) {
        int cur_cap;
        cin >> cur_cap;
        cap[node][node_cnt - 1] = cur_cap;
    }

    for (int node = 1; node <= m; node++) {
        int cur_cap;
        cin >> cur_cap;
        cap[0][node] = cur_cap;
    }

    for (int s = 1; s <= m; s++) {
        for (int e = m + 1; e < node_cnt - 1; e++) {
            cin >> cap[s][e];
        }
    }

    for (int s = 1; s <= m; s++) {
        for (int e = m + 1; e < node_cnt - 1; e++) {
            int cur_cost;
            cin >> cur_cost;
            cost[s][e] = cur_cost;
            cost[e][s] = -cur_cost;
        }
    }

    auto [flow, cost_total] = mcmf(cap, cost, 0, node_cnt - 1);

    cout << flow << '\n'
         << cost_total;

    return 0;
}