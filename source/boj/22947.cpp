// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<int>> pick(int n, int k) {
    vector<vector<int>> res;
    vector<int> cur;
    function<void(int, int)> dfs = [&](int idx, int cnt) {
        if (cnt == k) {
            res.push_back(cur);
            return;
        }
        for (int i = idx; i < n; i++) {
            cur.push_back(i);
            dfs(i + 1, cnt + 1);
            cur.pop_back();
        }
    };
    dfs(0, 0);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n);
    vector<int> indeg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        indeg[v]++;
    }

    int s = 0, e;
    for (int i = 0; i < n; i++) {
        if (adj[i].empty()) {
            e = i;
        }
    }

    ll ans = 1e18;

    auto combs = pick(n, k);
    for (auto comb : combs) {
        if (find(comb.begin(), comb.end(), s) != comb.end() || find(comb.begin(), comb.end(), e) != comb.end()) {
            continue;
        }
        vector<ll> a_new = a;
        for (auto i : comb) {
            a_new[i] = 0;
        }
        auto cur_indeg = indeg;
        vector<ll> dp = a_new;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                dp[v] = max(dp[v], dp[u] + a_new[v]);
                cur_indeg[v]--;
                if (cur_indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        ans = min(ans, dp[e]);
    }

    cout << ans << "\n";

    return 0;
}