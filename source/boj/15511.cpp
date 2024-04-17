#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool is_bipartite(vector<vector<int>> &adj, vector<int> &color, int u, int c)
{
    color[u] = c;
    for (int v : adj[u]) {
        if (color[v] == -1) {
            if (!is_bipartite(adj, color, v, 1 - c)) {
                return false;
            }
        }
        else if (color[v] == c) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> color(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            if (!is_bipartite(adj, color, i, 0)) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }
    cout << "POSSIBLE\n";

    return 0;
}