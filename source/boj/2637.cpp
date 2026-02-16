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
    vector<vector<pll>> adj(n + 1);
    vector<int> indeg(n + 1);
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[v].push_back({u, w});
        indeg[u]++;
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    queue<int> q;
    vector<int> cands;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            dp[i][i] = 1;
            cands.push_back(i);
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto &[nv, w] : adj[v]) {
            for (int i = 1; i <= n; i++) {
                dp[nv][i] += w * dp[v][i];
            }
            indeg[nv]--;
            if (indeg[nv] == 0) {
                q.push(nv);
            }
        }
    }

    for (int i = 0; i < cands.size(); i++) {
        cout << cands[i] << ' ' << dp[n][cands[i]];
        if (i != cands.size() - 1) {
            cout << '\n';
        }
    }

    return 0;
}