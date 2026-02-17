// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<bool> dag_dp(vector<vector<array<int, 2>>> &adj, int s, int e) {
    int n = adj.size();
    vector<int> indeg(n);
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            indeg[v]++;
        }
    }

    // remove unnecessary edges first
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (i != s && indeg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    vector<vector<bool>> reachable(n);
    reachable[s] = {true};
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }

            if (reachable[v].size() < reachable[u].size() + w) {
                reachable[v].resize(reachable[u].size() + w, false);
            }
            for (int i = 0; i < (int)reachable[u].size(); i++) {
                if (reachable[u][i]) {
                    reachable[v][i + w] = true;
                }
            }
        }
    }
    return reachable[e];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 2>>> adj1(n), adj2(n);

    for (int i = 0; i < m; i++) {
        int u, v, w1, w2;
        cin >> u >> v >> w1 >> w2;
        u--;
        v--;
        assert(u < v);
        adj1[u].push_back({v, w1});
        adj2[u].push_back({v, w2});
    }

    auto dp1 = dag_dp(adj1, 0, n - 1), dp2 = dag_dp(adj2, 0, n - 1);
    for (int i = 0; i < min(dp1.size(), dp2.size()); i++) {
        if (dp1[i] && dp2[i]) {
            cout << i;
            return 0;
        }
    }

    cout << "IMPOSSIBLE";

    return 0;
}