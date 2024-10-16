// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    int n;
    vector<int> parent;
    vector<int> size;
    Dsu(int n) : n(n) {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int u) {
        if (parent[u] == u) {
            return u;
        }
        return parent[u] = find(parent[u]);
    }

    int unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return 0;
        }
        if (size[u] < size[v]) {
            swap(u, v);
        }
        parent[v] = u;
        size[u] += size[v];
        return 1;
    }

    int get_size(int u) {
        return size[find(u)];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};

vector<ll> dijkstra(vector<vector<pll>> &adj_list, vector<int> &starts) {
    vector<ll> dist(adj_list.size(), LLONG_MAX);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for (int start : starts) {
        dist[start] = 0;
        pq.push({0, start});
    }

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist[u] < d) {
            continue;
        }

        for (auto &edge : adj_list[u]) {
            int v = edge.first;
            ll w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<int> get_depth(vector<vector<pll>> &adj_list, int root) {
    int n = adj_list.size();
    vector<int> depth(n, -1);
    queue<int> q;
    q.push(root);
    depth[root] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, _] : adj_list[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }

    return depth;
}

// lca sparse table
vector<vector<int>> make_lca_sparse_table(vector<vector<pll>> &adj_list, int root) {
    int n = adj_list.size();
    int logn = 32 - __builtin_clz(n);
    // logn by n because of cahce locality
    vector<vector<int>> parent(logn, vector<int>(n, -1));
    vector<int> depth(n, -1);
    queue<int> q;
    q.push(root);
    depth[root] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, _] : adj_list[u]) {
            if (depth[v] == -1) {
                parent[0][v] = u;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 1; i < logn; i++) {
        for (int u = 0; u < n; u++) {
            if (parent[i - 1][u] != -1) {
                parent[i][u] = parent[i - 1][parent[i - 1][u]];
            }
        }
    }

    return parent;
}

// minimum weight edge sparse table
// ret[i][u] = {w, v}
// where v is the vertex that is the (2^i)-th ancestor of u
// and w is the weight of the lightest edge between u and v
vector<vector<pll>> make_mwe_sparse_table(vector<vector<pll>> &adj_list, vector<vector<int>> &parent) {
    int n = adj_list.size();
    int logn = 32 - __builtin_clz(n);
    vector<vector<pll>> ret(logn, vector<pll>(n, {LLONG_MAX, -1}));
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj_list[u]) {
            if (parent[0][u] == v) {
                ret[0][u] = {w, v};
            }
        }
    }

    for (int i = 1; i < logn; i++) {
        for (int u = 0; u < n; u++) {
            int v = parent[i - 1][u];
            if (v != -1) {
                ret[i][u] = {min(ret[i - 1][u].first, ret[i - 1][v].first), ret[i - 1][v].second};
            }
        }
    }

    return ret;
}

// query the minimum weight edge between u and v
ll get_lightest_edge_weight(vector<vector<pll>> &mwe_sparse_table, vector<int> &depth, int u, int v) {
    int logn = mwe_sparse_table.size();
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    ll ret = LLONG_MAX;
    for (int i = logn - 1; i >= 0; i--) {
        if (depth[u] - depth[v] >= (1 << i)) {
            ret = min(ret, mwe_sparse_table[i][u].first);
            u = mwe_sparse_table[i][u].second;
        }
    }

    if (u == v) {
        return ret;
    }

    for (int i = logn - 1; i >= 0; i--) {
        if (mwe_sparse_table[i][u].second != mwe_sparse_table[i][v].second) {
            ret = min({ret, mwe_sparse_table[i][u].first, mwe_sparse_table[i][v].first});
            u = mwe_sparse_table[i][u].second;
            v = mwe_sparse_table[i][v].second;
        }
    }

    return min({ret, mwe_sparse_table[0][u].first, mwe_sparse_table[0][v].first});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, k, q;
    cin >> n >> m >> k >> q;

    vector<vector<pll>> adj_list(n + 1);
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    vector<int> starts(k);
    for (int i = 0; i < k; i++) {
        cin >> starts[i];
    }

    vector<ll> dist = dijkstra(adj_list, starts);

    Dsu dsu(n + 1);
    // the weight of the edge is the minimum distance from start edges
    vector<tuple<ll, int, int>> edges;
    for (int u = 1; u <= n; u++) {
        for (auto [v, d] : adj_list[u]) {
            edges.push_back({min(dist[u], dist[v]), u, v});
        }
    }

    // to maximize the distance from start edges,
    // sort the edges in descending order of weight
    sort(edges.begin(), edges.end(), greater<tuple<ll, int, int>>());
    vector<vector<pll>> mst(n + 1);
    for (auto [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            mst[u].push_back({v, w});
            mst[v].push_back({u, w});
        }
    }

    // now we should process the queries
    // (u, v) -> the weight of lightest edge in the path from u to v
    vector<vector<int>> parent = make_lca_sparse_table(mst, 1);
    vector<vector<pll>> mwe = make_mwe_sparse_table(mst, parent);
    vector<int> depth = get_depth(mst, 1);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        cout << get_lightest_edge_weight(mwe, depth, u, v) << '\n';
    }

    return 0;
}