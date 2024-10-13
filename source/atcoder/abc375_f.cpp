// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> edges;
    vector<vector<ll>> adj_mat_orig(n, vector<ll>(n, 1e14));
    for (int i = 0; i < n; i++) {
        adj_mat_orig[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int s, e, c;
        cin >> s >> e >> c;
        s--;
        e--;
        adj_mat_orig[s][e] = c;
        adj_mat_orig[e][s] = c;
        edges.push_back({s, e, c});
    }

    vector<vector<ll>> adj_mat = adj_mat_orig;
    vector<vector<int>> queries(q);
    for (int i = 0; i < q; i++) {
        int q_type;
        cin >> q_type;
        // destroy edge
        if (q_type == 1) {
            int idx;
            cin >> idx;
            idx--;
            adj_mat[edges[idx][0]][edges[idx][1]] = 1e14;
            adj_mat[edges[idx][1]][edges[idx][0]] = 1e14;
            queries[i] = {q_type, idx};
        }
        // calc dist
        // offline query, so store the query
        else {
            int s, e;
            cin >> s >> e;
            s--;
            e--;
            queries[i] = {q_type, s, e};
        }
    }

    // floyd
    for (int m = 0; m < n; m++) {
        for (int s = 0; s < n; s++) {
            for (int e = 0; e < n; e++) {
                adj_mat[s][e] = min(adj_mat[s][e], adj_mat[s][m] + adj_mat[m][e]);
            }
        }
    }

    // reverse queries
    reverse(queries.begin(), queries.end());
    vector<ll> ans;
    for (int i = 0; i < q; i++) {
        // restore edge
        if (queries[i][0] == 1) {
            int idx = queries[i][1];
            int s = edges[idx][0];
            int e = edges[idx][1];
            adj_mat[s][e] = adj_mat_orig[s][e];
            adj_mat[e][s] = adj_mat_orig[e][s];

            for (int start = 0; start < n; start++) {
                for (int end = 0; end < n; end++) {
                    adj_mat[start][end] = min(adj_mat[start][end], adj_mat[start][s] + adj_mat[s][e] + adj_mat[e][end]);
                    adj_mat[start][end] = min(adj_mat[start][end], adj_mat[start][e] + adj_mat[s][e] + adj_mat[s][end]);
                }
            }
        }

        else {
            int s = queries[i][1];
            int e = queries[i][2];
            ans.push_back(adj_mat[s][e] >= 1e14 ? -1 : adj_mat[s][e]);
        }
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}