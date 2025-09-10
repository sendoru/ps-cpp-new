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

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                adj[j].push_back(i);
            }
        }
    }

    vector<int> indeg(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            indeg[j]++;
        }
    }

    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> ans(n);
    int cur = n;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ans[u] = cur;
        cur--;
        for (int v : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                pq.push(v);
            }
        }
    }

    if (cur != 0) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}