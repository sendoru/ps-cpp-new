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
    vector<vector<vector<pii>>> adj(n, vector<vector<pii>>(1 << 10));
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        for (int j = 0; j < (1 << 10); j++) {
            adj[a][j].push_back({b, j ^ w});
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(1 << 10, false));
    queue<pii> q;
    q.push({0, 0});
    visited[0][0] = true;
    while (!q.empty()) {
        auto [u, mask] = q.front();
        q.pop();
        for (auto [v, next_mask] : adj[u][mask]) {
            if (!visited[v][next_mask]) {
                visited[v][next_mask] = true;
                q.push({v, next_mask});
            }
        }
    }

    int ans = 1e9;
    for (int i = 0; i < (1 << 10); i++) {
        if (visited[n - 1][i]) {
            ans = i;
            break;
        }
    }

    if (ans == 1e9) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}