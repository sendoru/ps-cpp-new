#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int dfs(int node, int cur_cc_no, vector<vector<int>> &adj_list,
        vector<int> &cc_nums)
{
    cc_nums[node] = cur_cc_no;
    int size = 1;
    for (int i = 0; i < adj_list[node].size(); i++) {
        if (cc_nums[adj_list[node][i]] == -1) {
            size += dfs(adj_list[node][i], cur_cc_no, adj_list, cc_nums);
        }
    }
    return size;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    // find sizes of each cc
    vector<int> cc_sizes;
    vector<int> cc_nums(n, -1);
    for (int i = 0; i < n; i++) {
        if (cc_nums[i] == -1) {
            cc_sizes.push_back(dfs(i, cc_sizes.size(), adj_list, cc_nums));
        }
    }
    vector<ll> edge_cnt_of_cc(cc_sizes.size(), 0);
    for (int i = 0; i < n; i++) {
        edge_cnt_of_cc[cc_nums[i]] += adj_list[i].size();
    }

    // becausei it's bidirectional graph
    for (int i = 0; i < edge_cnt_of_cc.size(); i++) {
        edge_cnt_of_cc[i] /= 2;
    }

    ll ans = 0;

    // edge count of complete graph with n nodes is n * (n - 1) / 2
    for (int i = 0; i < edge_cnt_of_cc.size(); i++) {
        ans += ((ll)cc_sizes[i] * (cc_sizes[i] - 1) / 2) - edge_cnt_of_cc[i];
    }

    cout << ans;

    return 0;
}