// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(vector<vector<ll>> &adj, ll n, bool maximize) {
    ll k = adj.size();

    vector<ll> tp_order;
    vector<ll> in_degree(k, 0);
    for (ll u = 0; u < k; u++) {
        for (ll v : adj[u]) {
            in_degree[v]++;
        }
    }

    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (ll i = 0; i < k; i++) {
        if (in_degree[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        ll u = pq.top();
        pq.pop();
        tp_order.push_back(u);
        for (ll v : adj[abs(u)]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                pq.push(v);
            }
        }
    }

    ll ret = 0;
    vector<ll> exps(k, 1);
    for (int i = 1; i < k; i++) {
        exps[i] = (exps[i - 1] * n) % MOD1;
    }

    ll idx = 0, num = maximize ? n - k : k - 1;
    while (idx < k) {
        ll exp = abs(tp_order[idx]);
        ret = (ret + exps[exp] * num) % MOD1;
        idx++;
        if (maximize) {
            num++;
        } else {
            num--;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k, p;
    cin >> n >> k >> p;

    vector<vector<ll>> adj(k), adj_rev(k);
    for (ll i = 0; i < p; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    ll max_res = solve(adj_rev, n, true);
    ll min_res = solve(adj, n, false);
    cout << (max_res - min_res + MOD1) % MOD1 << endl;
    return 0;
}