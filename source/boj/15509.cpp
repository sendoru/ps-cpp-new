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

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n);
    vector<int> sz;
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            continue;
        }
        int cnt = 0;
        queue<int> q;
        q.push(i);
        visited[i] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cnt++;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        sz.push_back(cnt);
    }

    vector<bool> dp(k + 1);
    dp[0] = true;
    for (int s : sz) {
        for (int i = k; i >= s; i--) {
            dp[i] = dp[i] || dp[i - s];
        }
    }

    cout << (dp[k] ? "SAFE" : "DOOMED");

    return 0;
}