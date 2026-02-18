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

    int n, m, c;
    cin >> n >> m >> c;
    vector<vector<array<ll, 2>>> adj(n);
    vector<ll> indeg(n);
    vector<ll> dp(n);
    for (int i = 0; i < n; i++) {
        cin >> dp[i];
    }

    for (int i = 0; i < c; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        indeg[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [u, w] : adj[v]) {
            dp[u] = max(dp[u], dp[v] + w);
            indeg[u]--;
            if (indeg[u] == 0) {
                q.push(u);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << dp[i] << '\n';
    }

    return 0;
}