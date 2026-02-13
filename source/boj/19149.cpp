// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> dists(const vector<vector<int>> &adj, int start) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

vector<int> get_parents(const vector<vector<int>> &adj, int root) {
    int n = adj.size();
    vector<int> parents(n, -1);
    queue<int> q;
    parents[root] = root;
    q.push(root);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (parents[v] == -1) {
                parents[v] = u;
                q.push(v);
            }
        }
    }
    return parents;
}

vector<int> get_postorder(const vector<vector<int>> &adj, int root) {
    int n = adj.size();
    vector<int> postorder;
    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
        postorder.push_back(u);
    };
    dfs(root);
    return postorder;
}

// how many nodes should be marked
// so that every node is within distance k from a marked node
int solve_inv(const vector<int> &parents, const vector<int> &postorder, int k) {
    int n = postorder.size();
    int res = 0;
    vector<int> dist_to_marked(n, 1e7);
    vector<int> dist_uncovered(n, 0);
    vector<bool> visited(n, false);
    // function<void(int)> dfs = [&](int u) {
    //     visited[u] = true;
    //     for (int v : adj[u]) {
    //         if (!visited[v]) {
    //             dfs(v);
    //             dist_to_marked[u] = min(dist_to_marked[u], dist_to_marked[v] + 1);
    //             dist_uncovered[u] = max(dist_uncovered[u], dist_uncovered[v] + 1);
    //         }
    //     }
    //     if (dist_to_marked[u] + dist_uncovered[u] <= k) {
    //         dist_uncovered[u] = -1e7;
    //     }
    //     if (dist_uncovered[u] == k) {
    //         res++;
    //         dist_to_marked[u] = 0;
    //         dist_uncovered[u] = -1e7;
    //     }
    // };
    // dfs(0);
    for (auto v : postorder) {
        if (dist_to_marked[v] + dist_uncovered[v] <= k) {
            dist_uncovered[v] = -1e7;
        }
        if (dist_uncovered[v] == k) {
            res++;
            dist_to_marked[v] = 0;
            dist_uncovered[v] = -1e7;
        }
        int u = parents[v];
        if (u != -1) {
            dist_to_marked[u] = min(dist_to_marked[u], dist_to_marked[v] + 1);
            dist_uncovered[u] = max(dist_uncovered[u], dist_uncovered[v] + 1);
        }
    }
    if (dist_uncovered[0] >= 0) {
        res++;
    }
    return res;
}

void solve(int k_lo, int k_hi, int inv_lo, int inv_hi, const vector<int> &parents, const vector<int> &postorder, vector<int> &ans_inv) {
    if (k_lo > k_hi) {
        return;
    }
    if (inv_lo == inv_hi) {
        for (int k = k_lo; k <= k_hi; k++) {
            ans_inv[k] = inv_lo;
        }
        return;
    }
    int k_mid = (k_lo + k_hi) / 2;
    int inv_mid = solve_inv(parents, postorder, k_mid);
    ans_inv[k_mid] = inv_mid;
    solve(k_lo, k_mid - 1, inv_mid, inv_hi, parents, postorder, ans_inv);
    solve(k_mid + 1, k_hi, inv_lo, inv_mid, parents, postorder, ans_inv);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist0 = dists(adj, 0);
    int farthest = max_element(dist0.begin(), dist0.end()) - dist0.begin();
    vector<int> dist1 = dists(adj, farthest);
    int radius = (*max_element(dist1.begin(), dist1.end()) + 1) / 2;

    vector<int> parents = get_parents(adj, 0);
    vector<int> postorder = get_postorder(adj, 0);

    vector<int> ans_inv(radius + 2, 0);
    solve(0, radius + 1, 0, n, parents, postorder, ans_inv);
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= radius; i++) {
        for (int j = ans_inv[i]; j < ans_inv[i - 1]; j++) {
            ans[j] = i;
        }
    }

    for (int k = 1; k <= n; k++) {
        cout << ans[k] << " ";
    }
    cout << "\n";

    return 0;
}