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
    vector<vector<int>> adj_mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        adj_mat[i][i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        v1--;
        v2--;
        adj_mat[v1][v2] = 1;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adj_mat[i][j] = adj_mat[i][j] || (adj_mat[i][k] && adj_mat[k][j]);
            }
        }
    }

    int s;
    cin >> s;
    for (int i = 0; i < s; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        v1--;
        v2--;
        if (adj_mat[v1][v2]) {
            cout << "-1\n";
        } else if (adj_mat[v2][v1]) {
            cout << "1\n";
        } else {
            cout << "0\n";
        }
    }

    return 0;
}