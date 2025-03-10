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

    ll n, k;
    cin >> n >> k;
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

    // subgraph_cnt[i][j] = number of subgraphs with size j in the subtree rooted at i and including i
    vector<vector<ll>> subgraph_cnt(n);
    fill(visited.begin(), visited.end(), false);

    function<void(int)> dfs2 = [&](int node) {
        visited[node] = true;
        subgraph_cnt[node] = {0, 0};
        subgraph_cnt[node][1] = 1;
        for (int next : adj_list[node]) {
            if (visited[next]) {
                continue;
            }
            dfs2(next);
            vector<ll> tmp = subgraph_cnt[node];
            for (int i = 1; i <= subtree_size[next]; i++) {
                for (int j = 1; j < subgraph_cnt[node].size(); j++) {
                    if (i + j > subtree_size[node]) {
                        break;
                    }
                    while (tmp.size() <= i + j) {
                        tmp.push_back(0);
                    }
                    __int128_t aa = (__int128_t)tmp[i + j] + (__int128_t)subgraph_cnt[node][j] * subgraph_cnt[next][i];
                    tmp[i + j] = (ll)min((__int128_t)1.5e18, (__int128_t)aa);
                }
            }
            subgraph_cnt[node] = tmp;
        }
    };
    dfs2(0);
    vector<ll> all_subgraph_cnt = subgraph_cnt[0];
    for (int i = 1; i < subgraph_cnt.size(); i++) {
        for (int j = 0; j < subgraph_cnt[i].size(); j++) {
            all_subgraph_cnt[j] += subgraph_cnt[i][j];
            all_subgraph_cnt[j] = min((ll)1.5e18, all_subgraph_cnt[j]);
        }
    }

    __int128_t cur = all_subgraph_cnt[0];
    for (int i = 1; i < all_subgraph_cnt.size(); i++) {
        cur += all_subgraph_cnt[i];
        if (cur >= k) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';

    return 0;
}