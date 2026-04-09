// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

class TreeDistQuery {
    int n, logn;
    int root;
    vector<ll> depths;
    vector<vector<ll>> lca_table;
    vector<vector<ll>> dist_table;

  public:
    TreeDistQuery(vector<ll> &parents, vector<ll> &dists_to_parent, vector<ll> &depths) {
        n = parents.size();
        root = find(parents.begin(), parents.end(), -1) - parents.begin();
        logn = 0;
        while ((1 << logn) < n) {
            logn++;
        }
        this->depths = depths;
        lca_table.assign(logn, vector<ll>(n));
        dist_table.assign(logn, vector<ll>(n));
        for (int i = 0; i < n; i++) {
            lca_table[0][i] = parents[i];
            dist_table[0][i] = dists_to_parent[i];
        }
        for (int i = 1; i < logn; i++) {
            for (int j = 0; j < n; j++) {
                if (lca_table[i - 1][j] == -1) {
                    lca_table[i][j] = -1;
                    dist_table[i][j] = dist_table[i - 1][j];
                } else {
                    lca_table[i][j] = lca_table[i - 1][lca_table[i - 1][j]];
                    dist_table[i][j] = dist_table[i - 1][j] + dist_table[i - 1][lca_table[i - 1][j]];
                }
            }
        }
    }

    ll dist(ll u, ll v) {
        if (depths[u] < depths[v]) {
            swap(u, v);
        }
        ll dist = 0;
        for (int i = logn - 1; i >= 0; i--) {
            if (lca_table[i][u] != -1 && depths[lca_table[i][u]] >= depths[v]) {
                dist += dist_table[i][u];
                u = lca_table[i][u];
            }
        }
        for (int i = logn - 1; i >= 0; i--) {
            if (lca_table[i][u] != lca_table[i][v]) {
                dist += dist_table[i][u] + dist_table[i][v];
                u = lca_table[i][u];
                v = lca_table[i][v];
            }
        }
        if (u != v) {
            dist += dist_table[0][u] + dist_table[0][v];
        }
        return dist;
    }
};

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        solve();
    }
}

void solve() {
    int n;
    cin >> n;
    if (n == 0) {
        exit(0);
    }
    vector<vector<array<ll, 2>>> adj(n);
    // unicycle graph
    for (int i = 0; i < n; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<vector<array<ll, 2>>> adj_clean(n);
    vector<ll> parents(n, -1), dists_to_parent(n, 0), depths(n, 0);
    array<ll, 3> cycle_edge = {-1, -1, -1};
    vector<bool> visited(n);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    dists_to_parent[0] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                adj_clean[u].push_back({v, w});
                adj_clean[v].push_back({u, w});
                parents[v] = u;
                dists_to_parent[v] = w;
                depths[v] = depths[u] + 1;
                q.push(v);
            } else if (v != parents[u]) {
                cycle_edge = {u, v, w};
            }
        }
    }

    TreeDistQuery tree_dist_query(parents, dists_to_parent, depths);

    int query_cnt;
    cin >> query_cnt;
    while (query_cnt--) {
        int u, v;
        cin >> u >> v;
        ll dist = tree_dist_query.dist(u, v);
        dist = min(dist, tree_dist_query.dist(u, cycle_edge[0]) + tree_dist_query.dist(cycle_edge[1], v) + cycle_edge[2]);
        dist = min(dist, tree_dist_query.dist(u, cycle_edge[1]) + tree_dist_query.dist(cycle_edge[0], v) + cycle_edge[2]);
        cout << dist << "\n";
    }
}