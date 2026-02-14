// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    vector<int> parent, size;
    Dsu(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) {
                swap(a, b);
            }
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dsu dsu(n + 1);
    vector<vector<int>> adj_mat(n + 1, vector<int>(n + 1, -1));
    for (int i = 0; i <= n; i++) {
        adj_mat[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dsu.merge(a, b);
        adj_mat[a][b] = adj_mat[b][a] = 1;
    }

    vector<pair<int, int>> min_cover_len(n + 1, {1e8, -1});

    // floyd
    for (int mid = 1; mid <= n; mid++) {
        for (int start = 1; start <= n; start++) {
            for (int end = 1; end <= n; end++) {
                if (adj_mat[start][mid] == -1 || adj_mat[mid][end] == -1) {
                    continue;
                }
                if (adj_mat[start][end] == -1 || adj_mat[start][end] > adj_mat[start][mid] + adj_mat[mid][end]) {
                    adj_mat[start][end] = adj_mat[start][mid] + adj_mat[mid][end];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int par = dsu.find(i);
        int cover_len = *max_element(adj_mat[i].begin() + 1, adj_mat[i].end());
        min_cover_len[par] = min(min_cover_len[par], {cover_len, i});
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (min_cover_len[i].second != -1) {
            ans.push_back(min_cover_len[i].second);
        }
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (int x : ans) {
        cout << x << "\n";
    }

    return 0;
}