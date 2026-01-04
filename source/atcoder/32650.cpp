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
    vector<ll> par, sz;
    Dsu(ll n) {
        par.resize(n);
        sz.resize(n, 1);
        for (ll i = 0; i < n; i++) {
            par[i] = i;
        }
    }
    void reset() {
        ll n = par.size();
        for (ll i = 0; i < n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }
    ll find(ll x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(ll x, ll y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
    }
    bool same(ll x, ll y) {
        return find(x) == find(y);
    }
    ll size(ll x) {
        return sz[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    vector<array<int, 3>> edges(m);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (ll i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        edges[i] = {w, u, v};
    }
    sort(edges.begin(), edges.end());
    vector<array<int, 3>> mst_edges;
    ll ans = 0;
    Dsu dsu(n + 1);
    for (auto& [w, u, v]: edges) {
        if (!dsu.same(u, v)) {
            dsu.unite(u, v);
            mst_edges.push_back({w, u, v});
            ans += w;
        }
    }

    set<int> unique_parents;
    for (int i = 0; i < n; i++) {
        unique_parents.insert(dsu.find(i));
    }
    if (unique_parents.size() > k) {
        cout << -1;
        return 0;
    }

    map<int, int> parent_min_edge;
    vector<bool> used(n, false);
    int used_cnt = 0;
    for (int i = 0; i < n; i++) {
        int u = dsu.find(i);
        if (parent_min_edge.find(u) == parent_min_edge.end() || a[parent_min_edge[u]] > a[i]) {
            parent_min_edge[u] = i;
        }
    }
    for (auto &[p, idx]: parent_min_edge) {
        used[idx] = true;
        used_cnt++;
        ans += a[idx];
        mst_edges.push_back({a[idx], idx, n});
    }

    while(used_cnt < k) {
        vector<vector<pii>> adj(n + 1);
        for (auto & [w, u, v]: mst_edges) {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        vector<int> parent(n + 1, -1);
        vector<bool> visited(n + 1, false);
        vector<pii> longest_edge_to_root(n + 1);
        queue<int> q;
        q.push(n);
        visited[n] = true;
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            for (auto& [nxt, w]: adj[curr]) {
                if (visited[nxt]) continue;
                visited[nxt] = true;
                parent[nxt] = curr;
                longest_edge_to_root[nxt] = max(longest_edge_to_root[curr], {w, nxt});
                q.push(nxt);
            }
        }
        array<int, 3> cand_remove = {-1, -1, -1};
        array<int, 3> cand_add = {-1, -1, -1};
        ll max_diff = 0;
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            auto [w, v] = longest_edge_to_root[i];
            ll diff = w - a[i];
            if (diff > max_diff) {
                max_diff = diff;
                cand_remove = {w, parent[v], v};
                cand_add = {a[i], i, n};
            }
        }
        if (max_diff == 0) break;
        ans -= max_diff;
        used[cand_add[1]] = true;
        used_cnt++;
        mst_edges.erase(remove(mst_edges.begin(), mst_edges.end(), cand_remove), mst_edges.end());
        swap(cand_remove[1], cand_remove[2]);
        mst_edges.erase(remove(mst_edges.begin(), mst_edges.end(), cand_remove), mst_edges.end());
        mst_edges.push_back(cand_add);
    }

    cout << ans;

    return 0;
}