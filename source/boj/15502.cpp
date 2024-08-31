#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        r--;
        for (int j = l; j + k <= r; j++) {
            adj[j].push_back(j + k);
            adj[j + k].push_back(j);
        }
    }

    ll cc_cnt = 0;
    vector<bool> visited(n);
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            continue;
        }
        cc_cnt++;
        queue<int> q;
        visited[i] = true;
        q.push(i);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int nxt : adj[cur]) {
                if (visited[nxt]) {
                    continue;
                }
                visited[nxt] = true;
                q.push(nxt);
            }
        }
    }

    ll ans = 1;
    for (int i = 0; i < cc_cnt; i++) {
        ans = (ans * 2) % MOD1;
    }

    cout << ans << '\n';

    return 0;
}