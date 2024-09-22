// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool bipartite_match(vector<vector<int>> &adj, vector<int> &prev, vector<bool> &visited, int v) {
    if (v == -1) {
        return true;
    }

    for (int u : adj[v]) {
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        if (bipartite_match(adj, prev, visited, prev[u])) {
            prev[u] = v;
            return true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        int n;
        cin >> n;
        if (cin.eof()) {
            break;
        }

        vector<vector<int>> adj(2 * n);

        for (int i = 0; i < n; i++) {
            string tmp;
            cin >> tmp;
            tmp.pop_back();
            int s = stoi(tmp);
            int degree;
            cin >> tmp;
            tmp = tmp.substr(1);
            tmp.pop_back();
            degree = stoi(tmp);
            for (int j = 0; j < degree; j++) {
                int e;
                cin >> e;
                adj[s].push_back(e);
                adj[e].push_back(s);
            }
        }

        vector<int> prev(2 * n, -1);
        int match = 0;
        vector<bool> visited(2 * n);
        for (int i = 0; i < n; i++) {
            if (bipartite_match(adj, prev, visited, i)) {
                match++;
            }
            fill(visited.begin(), visited.end(), false);
        }

        cout << match << '\n';
    }

    return 0;
}