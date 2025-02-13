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
    vector<pii> edges;
    vector<vector<pii>> adj_list(n);
    for (int i = 0; i < m; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        edges.push_back({s, e});
        adj_list[s].push_back({e, i});
        adj_list[e].push_back({s, i});
    }

    vector<bool> is_tree_edge(m, false);
    vector<bool> visited(n, false);
    vector<vector<int>> cc;
    vector<int> node_cc_no(n, -1);
    vector<int> edge_cc_no(m, -1);

    function<void(int)> dfs = [&](int cur) {
        visited[cur] = true;
        cc.back().push_back(cur);
        node_cc_no[cur] = cc.size() - 1;
        for (auto [nxt, edge_idx] : adj_list[cur]) {
            if (visited[nxt]) {
                continue;
            }
            is_tree_edge[edge_idx] = true;
            dfs(nxt);
        }
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cc.push_back({});
            dfs(i);
        }
    }

    for (int i = 0; i < m; i++) {
        edge_cc_no[i] = node_cc_no[edges[i].first];
    }

    vector<vector<int>> cc_edges(cc.size());
    for (int i = 0; i < m; i++) {
        if (!is_tree_edge[i]) {
            cc_edges[edge_cc_no[i]].push_back(i);
        }
    }

    // merged till now
    int cur_merged = 0;
    vector<bool> merged(cc.size(), false);

    vector<vector<int>> ans;
    for (int i = 0; i < cc_edges.size(); i++) {
        if (cur_merged == cc.size()) {
            break;
        }
        for (int j = 0; j < cc_edges[i].size(); j++) {
            while (cur_merged < cc.size() && (cur_merged == i || merged[cur_merged])) {
                cur_merged++;
            }
            if (cur_merged == cc.size()) {
                break;
            }
            // connect cur_merged with i
            ans.push_back({cc_edges[i][j], edges[cc_edges[i][j]].first, cc[cur_merged][0]});
            merged[cur_merged] = true;
        }
    }

    cout << cc.size() - 1 << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i][0] + 1 << ' ' << ans[i][1] + 1 << ' ' << ans[i][2] + 1 << endl;
    }

    return 0;
}