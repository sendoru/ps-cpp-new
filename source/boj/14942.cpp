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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<pii>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj_list[u].emplace_back(v, w);
        adj_list[v].emplace_back(u, w);
    }

    vector<int> par(n, 0);
    vector<int> par_dist(n, 0);
    function<void(int)> dfs = [&](int u) {
        for (auto [v, w] : adj_list[u]) {
            if (v == par[u]) {
                continue;
            }
            par[v] = u;
            par_dist[v] = w;
            dfs(v);
        }
    };

    dfs(0);

    vector<vector<int>> par_table(n, vector<int>(18, 0));
    vector<vector<int>> dist_table(n, vector<int>(18, 0));
    for (int i = 0; i < n; i++) {
        par_table[i][0] = par[i];
        dist_table[i][0] = par_dist[i];
    }

    for (int j = 1; j < 18; j++) {
        for (int i = 0; i < n; i++) {
            par_table[i][j] = par_table[par_table[i][j - 1]][j - 1];
            dist_table[i][j] = dist_table[i][j - 1] + dist_table[par_table[i][j - 1]][j - 1];
        }
    }

    for (int i = 0; i < n; i++) {
        int cur = i;
        int dist = 0;
        for (int j = 17; j >= 0; j--) {
            if (cur == 0) {
                break;
            }
            if (a[i] - dist >= dist_table[cur][j]) {
                dist += dist_table[cur][j];
                cur = par_table[cur][j];
            }
        }
        cout << cur + 1 << "\n";
    }

    return 0;
}