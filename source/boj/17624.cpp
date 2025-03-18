// #include "atcoder/all"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")

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

    int n, b;
    cin >> n >> b;
    vector<bool> is_black(n);
    for (int i = 0; i < b; i++) {
        int x;
        cin >> x;
        is_black[x - 1] = true;
    }
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        adj_list[s].push_back(e);
        adj_list[e].push_back(s);
    }

    vector<int> subtree_size(n, -1);
    vector<bool> visited(n, false);
    function<int(int)> dfs = [&](int node) {
        visited[node] = true;
        subtree_size[node] = 1;
        for (int next : adj_list[node]) {
            if (visited[next]) {
                continue;
            }
            subtree_size[node] += dfs(next);
        }
        return subtree_size[node];
    };
    dfs(0);

    // dp[i][j] = {min, max} number of black nodes in a subgraph of size j rooted at i
    vector<vector<pii>> dp(n);
    fill(visited.begin(), visited.end(), false);

    function<void(int)> dfs2 = [&](int node) {
        visited[node] = true;
        dp[node] = {{0, 0}};
        if (is_black[node]) {
            dp[node].push_back({1, 1});
        } else {
            dp[node].push_back({0, 0});
        }
        for (int next : adj_list[node]) {
            if (visited[next]) {
                continue;
            }
            dfs2(next);
            vector<pii> tmp = dp[node];
            for (int i = 1; i <= subtree_size[next]; i++) {
                for (int j = 1; j < dp[node].size(); j++) {
                    if (i + j > subtree_size[node]) {
                        break;
                    }
                    while (tmp.size() <= i + j) {
                        tmp.push_back({n, 0});
                    }
                    tmp[i + j].first = min(tmp[i + j].first, dp[node][j].first + dp[next][i].first);
                    tmp[i + j].second = max(tmp[i + j].second, dp[node][j].second + dp[next][i].second);
                }
            }
            dp[node] = tmp;
        }
    };
    dfs2(0);
    vector<pii> all_subtrees = dp[0];
    for (vector<pii> &subtree : dp) {
        for (int i = 0; i < subtree.size(); i++) {
            all_subtrees[i].first = min(all_subtrees[i].first, subtree[i].first);
            all_subtrees[i].second = max(all_subtrees[i].second, subtree[i].second);
        }
    }

    int q;
    cin >> q;
    int ans = 0;
    while (q--) {
        int x, y;
        cin >> x >> y;

        if (all_subtrees[x].first <= y && y <= all_subtrees[x].second) {
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}