// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// assume that adj is a tree
vector<int> get_centers(vector<vector<int>> &adj) {
    vector<int> ret;
    int n = adj.size();
    vector<int> max_min_dists(n, 1e9);
    for (int i = 0; i < n; i++) {
        vector<int> dist(n, 1e9);
        dist[i] = 0;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] == 1e9) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        max_min_dists[i] = *max_element(dist.begin(), dist.end());
    }

    int min_dist = *min_element(max_min_dists.begin(), max_min_dists.end());
    for (int i = 0; i < n; i++) {
        if (max_min_dists[i] == min_dist) {
            ret.push_back(i);
        }
    }

    return ret;
}

pll get_hash(vector<vector<int>> &adj, int root, vector<bool> &visited) {
    ll ret;
    ll len = 0;
    visited[root] = true;

    vector<pll> child_hashes;
    for (int v : adj[root]) {
        if (visited[v]) {
            continue;
        }

        auto child_hash = get_hash(adj, v, visited);
        child_hashes.push_back(child_hash);
    }

    sort(child_hashes.begin(), child_hashes.end());
    ret = 1;
    len = 1;
    for (const auto [child_hash, child_len] : child_hashes) {
        ret <<= child_len;
        len += child_len;
        ret += child_hash;
    }
    ret <<= 1;
    len += 1;
    return {ret, len};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<pll> hashes;
    while (n--) {
        int s;
        cin >> s;
        vector<vector<int>> adj(s);
        for (int i = 0; i < s - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> centers = get_centers(adj);
        vector<bool> visited(s, false);
        if (centers.size() == 1) {
            auto hash = get_hash(adj, centers[0], visited);
            hashes.push_back(hash);
        } else {
            auto hash1 = get_hash(adj, centers[0], visited);
            visited.assign(s, false);
            auto hash2 = get_hash(adj, centers[1], visited);
            if (hash1.first < hash2.first) {
                hashes.push_back(hash1);
            } else {
                hashes.push_back(hash2);
            }
        }
    }

    sort(hashes.begin(), hashes.end());
    hashes.erase(unique(hashes.begin(), hashes.end()), hashes.end());

    cout << hashes.size() << "\n";

    return 0;
}