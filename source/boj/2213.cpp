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
    vector<ll> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<ll, 2>> dp(n, array<ll, 2>{-1, -1});
    vector<vector<int>> selected = adj;
    for (int i = 0; i < n; i++) {
        fill(selected[i].begin(), selected[i].end(), -1);
    }
    function<void(int)> dfs = [&](int u) {
        dp[u][0] = 0;
        dp[u][1] = weights[u];
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i];
            if (dp[v][0] == -1) {
                dfs(v);
                if (dp[v][0] > dp[v][1]) {
                    dp[u][0] += dp[v][0];
                    selected[u][i] = 0;
                } else {
                    dp[u][0] += dp[v][1];
                    selected[u][i] = 1;
                }
                dp[u][1] += dp[v][0];
            }
        }
    };

    dfs(0);
    cout << max(dp[0][0], dp[0][1]) << '\n';

    vector<int> ans;
    function<void(int, int)> trace = [&](int u, int sel) {
        if (sel == 1) {
            ans.push_back(u);
        }
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i];
            if (selected[u][i] != -1) {
                if (sel) {
                    trace(v, 0);
                } else {
                    trace(v, selected[u][i]);
                }
            }
        }
    };
    if (dp[0][0] > dp[0][1]) {
        trace(0, 0);
    } else {
        trace(0, 1);
    }

    sort(ans.begin(), ans.end());
    for (int x : ans) {
        cout << x + 1 << ' ';
    }

    return 0;
}