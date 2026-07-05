// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> bfs_dists(const vector<vector<int>> &adj, int s) {
    int n = adj.size();
    vector<int> dists(n, -1);
    queue<int> q;
    dists[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (dists[u] == -1) {
                dists[u] = dists[v] + 1;
                q.push(u);
            }
        }
    }
    return dists;
}

vector<int> bfs_parents(const vector<vector<int>> &adj, int s) {
    int n = adj.size();
    vector<int> parents(n, -1);
    queue<int> q;
    parents[s] = s;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (parents[u] == -1) {
                parents[u] = v;
                q.push(u);
            }
        }
    }
    return parents;
}

vector<int> get_diameter_nodes(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> dists_from_0 = bfs_dists(adj, 0);
    int farthest_1 = max_element(dists_from_0.begin(), dists_from_0.end()) - dists_from_0.begin();
    vector<int> dists_from_f1 = bfs_dists(adj, farthest_1);
    int farthest_2 = max_element(dists_from_f1.begin(), dists_from_f1.end()) - dists_from_f1.begin();
    vector<int> parents_from_f1 = bfs_parents(adj, farthest_1);
    vector<int> res;
    int v = farthest_2;
    while (v != farthest_1) {
        res.push_back(v);
        v = parents_from_f1[v];
    }
    res.push_back(farthest_1);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        adj[s].push_back(e);
        adj[e].push_back(s);
    }

    auto diameter_nodes = get_diameter_nodes(adj);
    int m = diameter_nodes.size();
    int idx = (m - 1) / 2;
    cout << m << '\n';
    cout << diameter_nodes[idx] + 1 << ' ';
    for (int i = 1; i < m; i++) {
        idx = idx + i * (i % 2 == 1 ? 1 : -1);
        cout << diameter_nodes[idx] + 1 << ' ';
    }

    return 0;
}