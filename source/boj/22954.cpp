// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Edge {
    int no, l, r;
    Edge() : no(0), l(0), r(0) {}
    Edge(int no, int l, int r) : no(no), l(l), r(r) {}
};

struct Dsu {
    vector<int> roots, sizes;
    Dsu(int n) : roots(n + 1), sizes(n + 1, 1) {
        iota(roots.begin(), roots.end(), 0);
    }

    int find(int u) {
        if (roots[u] == u)
            return u;
        return roots[u] = find(roots[u]);
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;
        if (sizes[u] < sizes[v])
            swap(u, v);
        roots[v] = u;
        sizes[u] += sizes[v];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i].no = i + 1;
        cin >> edges[i].l >> edges[i].r;
    }

    int cc_cnt = 0;
    vector<bool> visited(n + 1, false);
    vector<vector<int>> adj_list(n + 1);
    vector<int> cc_sizes;
    for (auto [_, l, r] : edges) {
        adj_list[l].push_back(r);
        adj_list[r].push_back(l);
    }

    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        cc_sizes.back()++;
        for (int v : adj_list[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cc_cnt++;
            cc_sizes.push_back(0);
            dfs(i);
        }
    }

    if (cc_cnt >= 3) {
        cout << -1;
        return 0;
    }

    if (cc_cnt == 2) {
        if (cc_sizes[0] == cc_sizes[1]) {
            cout << -1;
            return 0;
        }

        Dsu dsu(n + 1);
        vector<Edge> edges_used;
        for (auto [no, l, r] : edges) {
            if (!dsu.same(l, r)) {
                dsu.merge(l, r);
                edges_used.push_back({no, l, r});
            }
        }
        vector<int> cc1, cc2;
        for (int i = 1; i <= n; i++) {
            if (dsu.same(i, 1)) {
                cc1.push_back(i);
            } else {
                cc2.push_back(i);
            }
        }

        cout << cc1.size() << " " << cc2.size() << "\n";

        for (int v : cc1) {
            cout << v << " ";
        }
        cout << "\n";
        for (auto [no, l, r] : edges_used) {
            if (dsu.same(l, 1)) {
                cout << no << " ";
            }
        }
        cout << "\n";

        for (int v : cc2) {
            cout << v << " ";
        }
        cout << "\n";
        for (auto [no, l, r] : edges_used) {
            if (!dsu.same(l, 1)) {
                cout << no << " ";
            }
        }
    }

    if (n <= 2) {
        cout << -1;
        return 0;
    }

    Dsu dsu(n + 1);
    vector<Edge> edges_used;
    vector<int> degree(n + 1);
    for (auto [no, l, r] : edges) {
        if (!dsu.same(l, r)) {
            dsu.merge(l, r);
            edges_used.push_back({no, l, r});
            degree[l]++;
            degree[r]++;
        }
    }

    int leaf;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            leaf = i;
            break;
        }
    }

    cout << 1 << " " << n - 1 << "\n";

    cout << leaf << "\n";
    cout << "\n";

    for (int i = 1; i <= n; i++) {
        if (i != leaf) {
            cout << i << " ";
        }
    }
    cout << "\n";

    for (auto [no, l, r] : edges_used) {
        if (l != leaf && r != leaf) {
            cout << no << " ";
        }
    }

    return 0;
}