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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // start from node 0
    // make dfs spanning tree
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    function<void(vector<vector<int>>&, vector<int>&, int)> dfs = [&](vector<vector<int>>& adj, vector<int>& parents, int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                parents[v] = u;
                dfs(adj, parents, v);
            }
        }
    };

    dfs(adj, parent, 0);
    
    // graph not including the tree edges
    vector<vector<int>> adj_c(n);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            // only excluding u->v when u == parent[v]
            if (parent[v] != u) {
                adj_c[u].push_back(v);
            }
        }
    }


    visited.assign(n, false);
    vector<int> parent_c(n, -1);
    dfs(adj_c, parent_c, 1);
    int visited_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            visited_cnt++;
        }
    }


    if (visited_cnt != n) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        cout << parent_c[0] + 1 << '\n';
        cout << parent[1] + 1 << '\n';
        for (int i = 2; i < n; i++) {
            cout << parent[i] + 1 << ' ' << parent_c[i] + 1 << '\n';
        }
    }

    return 0;
}