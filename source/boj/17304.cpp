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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj_list(n);
    vector<pii> edges(m);
    for (int i = 0; i < m; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        adj_list[s].push_back(e);
        edges[i] = {s, e};
    }

    for (int i = 0; i < n; i++) {
        sort(adj_list[i].begin(), adj_list[i].end());
    }

    vector<vector<int>> adj_bidir(n);
    vector<bool> visited(n, false);

    for (auto [s, e] : edges) {
        auto iter = lower_bound(adj_list[e].begin(), adj_list[e].end(), s);
        if (iter != adj_list[e].end() && *iter == s) {
            adj_bidir[s].push_back(e);
        } else {
            visited[e] = true;
        }
    }

    function<bool(int, int)> has_cycle = [&](int v, int parent) -> bool {
        visited[v] = true;
        bool ret = false;
        for (int u : adj_bidir[v]) {
            if (u == parent) {
                continue;
            }
            if (visited[u]) {
                ret = true;
            } else {
                ret |= has_cycle(u, v);
            }
        }
        return ret;
    };

    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            has_cycle(i, -1);
        }
    }

    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            ans = ans && has_cycle(i, -1);
        }
    }

    cout << (ans ? "YES" : "NO") << '\n';

    return 0;
}