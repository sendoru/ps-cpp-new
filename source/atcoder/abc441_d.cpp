// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll n, m, l, s, t;
vector<vector<pll>> adj;
vector<vector<ll>> dists;

void dfs(int v, ll cur_dist, int depth) {
    if (depth == l) {
        dists[v].push_back(cur_dist);
        return;
    }
    for (auto [nv, w] : adj[v]) {
        dfs(nv, cur_dist + w, depth + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> l >> s >> t;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        ll s, e, w;
        cin >> s >> e >> w;
        s--, e--;
        adj[s].emplace_back(e, w);
    }

    dists.resize(n);
    dfs(0, 0, 0);
    vector<int> ans;
    for (int i = 0; i < dists.size(); i++) {
        for (ll d : dists[i]) {
            if (d >= s && d <= t) {
                ans.push_back(i + 1);
                break;
            }
        }
    }
    for (int v : ans) {
        cout << v << " ";
    }
    return 0;
}