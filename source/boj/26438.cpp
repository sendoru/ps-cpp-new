#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// get the count of reachable vertices from v, including v itself
int dfs(vector<vector<int>> &adj_list, vector<int> &cnt, int v) {
    if (cnt[v] != -1) {
        return cnt[v];
    }
    cnt[v] = 1;
    for (int u : adj_list[v]) {
        cnt[v] += dfs(adj_list, cnt, u);
    }
    return cnt[v];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<int> cap(n);
        for (int i = 0; i < n; i++) {
            cin >> cap[i];
        }
        vector<vector<int>> adj_list(n);
        for (int i = 0; i < n - 1; i++) {
            int s, e;
            cin >> s >> e;
            s--;
            e--;
            if (cap[s] > cap[e]) {
                adj_list[s].push_back(e);
            } else if (cap[s] < cap[e]) {
                adj_list[e].push_back(s);
            }
        }

        int ans = 0;
        vector<int> cnt(n, -1);
        for (int i = 0; i < n; i++) {
            ans = max(ans, dfs(adj_list, cnt, i));
        }

        cout << "Case #" << t << ": " << ans << '\n';
    }

    return 0;
}