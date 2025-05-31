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
    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int ans = (1 << 30) - 1;

    for (int bit = 30; bit >= 0; bit--) {
        // 1 << bit를 포함하지 않는 간선만 남김
        vector<vector<pii>> adj_new(n);
        for (int u = 0; u < n; u++) {
            for (const auto &[v, w] : adj[u]) {
                if ((w & (1 << bit)) == 0) {
                    adj_new[u].emplace_back(v, w);
                }
            }
        }

        // bfs
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &[nxt, w] : adj_new[cur]) {
                if (!visited[nxt]) {
                    visited[nxt] = true;
                    q.push(nxt);
                }
            }
        }

        // n - 1이 방문 가능하면
        if (visited[n - 1]) {
            adj = adj_new;      // 간선을 갱신
            ans &= ~(1 << bit); // bit를 0으로 설정
        }
    }

    cout << ans << '\n';

    return 0;
}