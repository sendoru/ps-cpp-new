// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<ll>> combine_min_dist(const vector<vector<ll>> &adj1, const vector<vector<ll>> &adj2) {
    int n = adj1.size();
    vector<vector<ll>> res(n, vector<ll>(n, (ll)2e18));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] = min(res[i][j], adj1[i][k] + adj2[k][j]);
            }
        }
    }
    return res;
}

vector<vector<ll>> min_dist_power(const vector<vector<ll>> &adj, int p) {
    int n = adj.size();
    vector<vector<ll>> res = adj;
    vector<vector<ll>> cur = adj;
    p--;
    while (p > 0) {
        if (p & 1) {
            res = combine_min_dist(res, cur);
        }
        cur = combine_min_dist(cur, cur);
        p >>= 1;
    }
    return res;
}
vector<vector<ll>> min_dist_power_naive(const vector<vector<ll>> &adj, int p) {
    int n = adj.size();
    vector<vector<ll>> res = adj;
    for (int i = 1; i < p; i++) {
        res = combine_min_dist(res, adj);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<vector<ll>> adj_mat(n, vector<ll>(n, (ll)2e18));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj_mat[i][j];
        }
    }

    auto min_dist = min_dist_power(adj_mat, k);
    for (int i = 0; i < n; i++) {
        cout << min_dist[i][i] << '\n';
    }

    return 0;
}