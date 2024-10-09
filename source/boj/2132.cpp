// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> bfs(vector<vector<int>> &adj, vector<ll> &node_w, int start)
{
    vector<ll> dist(adj.size(), -1);
    queue<int> q;
    q.push(start);
    dist[start] = node_w[start];
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int next : adj[cur]) {
            if (dist[next] == -1) {
                dist[next] = dist[cur] + node_w[next];
                q.push(next);
            }
        }
    }
    return dist;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> node_w(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        cin >> node_w[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<ll> dist = bfs(adj, node_w, 0);
    ll farthest = max_element(dist.begin(), dist.end()) - dist.begin();
    dist = bfs(adj, node_w, farthest);
    ll farthest_2 = max_element(dist.begin(), dist.end()) - dist.begin();
    ll diameter = dist[farthest_2];

    cout << diameter << ' ' << min(farthest, farthest_2) + 1;

    return 0;
}