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
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        vector<int> v(k);
        for (int j = 0; j < k; j++) {
            cin >> v[j];
            v[j]--;
        }
        for (int j = 0; j < k - 1; j++) {
            adj[v[j]].push_back(v[j + 1]);
        }
    }

    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indeg[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> ans;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans.push_back(u);
        for (int v : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    if (ans.size() != n) {
        cout << 0;
    } else {
        for (int x : ans) {
            cout << x + 1 << "\n";
        }
    }

    return 0;
}