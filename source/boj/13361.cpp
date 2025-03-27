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
    vector<pll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    vector<pll> v_comp(n);
    vector<ll> vals;
    for (int i = 0; i < n; i++) {
        vals.push_back(v[i].first);
        vals.push_back(v[i].second);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    for (int i = 0; i < n; i++) {
        v_comp[i].first = lower_bound(vals.begin(), vals.end(), v[i].first) - vals.begin();
        v_comp[i].second = lower_bound(vals.begin(), vals.end(), v[i].second) - vals.begin();
    }

    vector<vector<int>> adj_list(vals.size());
    for (int i = 0; i < n; i++) {
        adj_list[v_comp[i].first].push_back(v_comp[i].second);
        adj_list[v_comp[i].second].push_back(v_comp[i].first);
    }

    vector<bool> visited(vals.size(), false);
    vector<int> cc_nodes;

    // dfs, finds all nodes in a connected component
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        cc_nodes.push_back(u);
        for (int v : adj_list[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
    };

    ll ans = 0;

    for (int i = 0; i < vals.size(); i++) {
        if (!visited[i]) {
            cc_nodes.clear();
            dfs(i);
            ll tmp = 0;
            vector<pii> cc_edges;
            for (auto node : cc_nodes) {
                for (auto next : adj_list[node]) {
                    cc_edges.push_back({node, next});
                }
            }
            for (pii edge : cc_edges) {
                tmp += vals[edge.first] + vals[edge.second];
            }
            ans += tmp / 2;

            // if tree
            if (cc_edges.size() / 2 == cc_nodes.size() - 1) {
                int max = *max_element(cc_nodes.begin(), cc_nodes.end());
                for (auto node : cc_nodes) {
                    if (node != max) {
                        ans -= vals[node];
                    }
                }
            } else {
                for (auto node : cc_nodes) {
                    ans -= vals[node];
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}