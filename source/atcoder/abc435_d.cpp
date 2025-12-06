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
    vector<vector<int>> adj_list(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // reversed
        adj_list[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);

    int q;
    cin >> q;
    while(q--) {
        int qt, v;
        cin >> qt >> v;
        if (qt == 1) {
            if (visited[v]) {
                continue;
            }
            queue<int> q;
            q.push(v);
            visited[v] = true;
            while(!q.empty()) {
                int cur = q.front();
                q.pop();
                for (int nxt : adj_list[cur]) {
                    if (!visited[nxt]) {
                        visited[nxt] = true;
                        q.push(nxt);
                    }
                }
            }
        }
        else {
            cout << (visited[v] ? "Yes" : "No") << "\n";
        }
    }

    return 0;
}