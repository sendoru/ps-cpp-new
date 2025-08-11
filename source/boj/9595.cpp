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

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    while (true) {
        string edge;
        cin >> edge;
        if (!cin.good()) {
            break;
        }
        auto pos = edge.find('-');
        int s = stoi(edge.substr(0, pos));
        int e = stoi(edge.substr(pos + 1));
        adj[s - 1].push_back(e - 1);
        adj[e - 1].push_back(s - 1);
    }

    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }

    // 4-coloring
    vector<int> color(n, -1);
    function<bool(int, int)> dfs = [&](int node, int c) -> bool {
        color[node] = c;
        for (int n_node : adj[node]) {
            if (color[n_node] == c) {
                color[node] = -1;
                return false;
            } else if (color[n_node] == -1) {
                bool cur_valid = false;
                for (int next_c = 0; next_c < 4; next_c++) {
                    if (next_c != c) {
                        cur_valid = dfs(n_node, next_c);
                        if (cur_valid) {
                            break;
                        }
                    }
                }
                if (!cur_valid) {
                    color[node] = -1;
                    return false;
                }
            }
        }
        return true;
    };

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            dfs(i, 0);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << color[i] + 1 << "\n";
    }

    return 0;
}