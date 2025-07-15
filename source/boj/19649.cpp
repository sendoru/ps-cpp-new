// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

tuple<vector<vector<int>>, vector<vector<int>>, vector<int>> get_scc(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> scc;
    vector<vector<int>> scc_adj;
    vector<int> component(n, -1);
    vector<int> postorder;
    vector<bool> visited(n, false);

    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int nxt : adj[node]) {
            if (!visited[nxt]) {
                dfs(nxt);
            }
        }
        postorder.push_back(node);
    };
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    int scc_count = 0;
    vector<vector<int>> adj_inv(n);
    for (int i = 0; i < n; i++) {
        for (int nxt : adj[i]) {
            adj_inv[nxt].push_back(i);
        }
    }
    visited.assign(n, false);
    function<void(int)> dfs_inv = [&](int node) {
        visited[node] = true;
        component[node] = scc_count;
        scc.back().push_back(node);
        for (int nxt : adj_inv[node]) {
            if (!visited[nxt]) {
                dfs_inv(nxt);
            }
        }
    };
    while (!postorder.empty()) {
        int node = postorder.back();
        postorder.pop_back();
        if (!visited[node]) {
            scc.push_back({});
            dfs_inv(node);
            scc_count++;
        }
    }
    scc_adj.resize(scc_count);
    for (int i = 0; i < n; i++) {
        for (int nxt : adj[i]) {
            if (component[i] != component[nxt]) {
                scc_adj[component[i]].push_back(component[nxt]);
            }
        }
    }
    for (auto &vec : scc_adj) {
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
    }
    return {scc, scc_adj, component};
}

int solve_dp(vector<vector<int>> &adj, vector<int> &vals, int node, vector<int> &dp) {
    if (dp[node] != -1)
        return dp[node];
    dp[node] = vals[node];
    for (int nxt : adj[node]) {
        dp[node] = max(dp[node], vals[node] + solve_dp(adj, vals, nxt, dp));
    }
    return dp[node];
}

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
        u--;
        v--;
        adj[u].push_back(v);
    }
    int k;
    cin >> k;
    k--;
    auto [scc, scc_adj, component] = get_scc(adj);
    vector<int> scc_size(scc.size(), 0);
    for (int i = 0; i < n; i++) {
        scc_size[component[i]]++;
    }
    int scc_k = component[k];
    vector<vector<int>> scc_ad_inv(scc.size());
    for (int i = 0; i < scc.size(); i++) {
        for (int nxt : scc_adj[i]) {
            scc_ad_inv[nxt].push_back(i);
        }
    }
    vector<bool> visited(scc.size(), false);
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int nxt : scc_ad_inv[node]) {
            if (!visited[nxt]) {
                dfs(nxt);
            }
        }
    };
    dfs(scc_k);
    vector<int> vals(scc.size(), 0);
    for (int i = 0; i < scc.size(); i++) {
        if (visited[i]) {
            vals[i] = scc_size[i];
        }
    }
    vector<int> dp(scc.size(), -1);
    for (int i = 0; i < scc.size(); i++) {
        if (visited[i]) {
            solve_dp(scc_adj, vals, i, dp);
        }
    }

    int max_dp = *max_element(dp.begin(), dp.end());

    vector<int> max_scc;
    for (int i = 0; i < scc.size(); i++) {
        if (dp[i] == max_dp) {
            max_scc.push_back(i);
        }
    }

    int ans = max_dp;
    if (scc[scc_k].size() == 1) {
        ans -= 2;
    } else {
        ans -= 1;
    }

    if (ans == 0) {
        cout << 0;
        return 0;
    }

    vector<int> max_nodes;
    for (int i : max_scc) {
        for (int node : scc[i]) {
            if (node != k) {
                max_nodes.push_back(node);
            }
        }
    }

    cout << *min_element(max_nodes.begin(), max_nodes.end()) + 1 << ' ' << ans << '\n';

    return 0;
}
