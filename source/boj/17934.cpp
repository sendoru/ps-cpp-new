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

    int n, s, t;
    cin >> n >> s >> t;
    vector<unordered_set<int>> adj(n);
    vector<bool> inv(n, false);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'C') {
            inv[i] = true;
        }
        int deg;
        cin >> deg;
        for (int j = 0; j < deg; j++) {
            int v;
            cin >> v;
            adj[i].insert(v);
        }
    }

    queue<int> q;
    vector<int> dist(n, -1);
    q.push(s);
    dist[s] = 0;
    unordered_set<int> not_visited;
    for (int i = 0; i < n; i++) {
        if (i != s) {
            not_visited.insert(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (inv[u]) {
            vector<int> visited;
            for (auto v : not_visited) {
                if (!adj[u].count(v) && dist[v] == -1) {
                    visited.push_back(v);
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
            for (auto v : visited) {
                not_visited.erase(v);
            }
        } else {
            for (auto v : adj[u]) {
                if (dist[v] == -1) {
                    not_visited.erase(v);
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    if (dist[t] == -1) {
        cout << "impossible";
    } else {
        cout << dist[t];
    }

    return 0;
}