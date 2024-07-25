// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int bfs(vector<vector<int>> &adj, vector<bool> &removed, vector<int> &start) {
    queue<int> q;
    for (auto i : start) {
        q.push(i);
    }

    int ret = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int nxt : adj[cur]) {
            if (removed[nxt] == false) {
                removed[nxt] = true;
                ret++;
                q.push(nxt);
            }
        }
    }

    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> pre(n);
    for (int i = 0; i < m; i++) {
        char a, b;
        cin >> a >> b;
        adj[a - 'A'].push_back(b - 'A');
        pre[b - 'A']++;
    }

    vector<bool> removed(n, false);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        char c;
        cin >> c;
        removed[c - 'A'] = true;
    }

    vector<int> start;
    for (int i = 0; i < n; i++) {
        if (pre[i] == 0 && !removed[i]) {
            start.push_back(i);
        }
    }

    cout << bfs(adj, removed, start);
}