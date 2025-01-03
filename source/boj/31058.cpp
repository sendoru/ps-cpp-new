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

    vector<vector<pll>> adj_list(n + 1);
    vector<vector<pll>> adj_list_rev(n + 1);
    vector<ll> in_degree(n + 1, 0);
    vector<ll> out_degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        adj_list[a].push_back({b, c});
        adj_list_rev[b].push_back({a, c});
        in_degree[b]++;
        out_degree[a]++;
    }

    for (int i = 1; i <= n; i++) {
        sort(adj_list[i].begin(), adj_list[i].end(), [](const pll &a, const pll &b) {
            return a.second < b.second;
        });
    }

    for (int i = 1; i <= n; i++) {
        sort(adj_list_rev[i].begin(), adj_list_rev[i].end(), [](const pll &a, const pll &b) {
            return a.second < b.second;
        });
    }

    vector<ll> ans(n + 1, 0);
    vector<ll> max_len(n + 1, -1);
    vector<ll> first_edge_w(n + 1, 4e18);
    vector<ll> second_edge_w(n + 1, 4e18);
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] == 0) {
            pq.push({-(ll)1e13, -1, i});
            ans[i] = 0;
            max_len[i] = 0;
        }
    }

    ll pushed_order = 0;

    while (!pq.empty()) {
        auto [last_edge, _, node] = pq.top();
        ll len = max_len[node];
        pq.pop();
        for (auto [pre, pre_edge_w] : adj_list_rev[node]) {
            out_degree[pre]--;
            if (max_len[pre] < len + 1 || (max_len[pre] == len + 1 && first_edge_w[pre] > pre_edge_w) || (max_len[pre] == len + 1 && first_edge_w[pre] == pre_edge_w && second_edge_w[pre] > last_edge)) {
                max_len[pre] = len + 1;
                first_edge_w[pre] = pre_edge_w;
                second_edge_w[pre] = last_edge;
                ans[pre] = ans[node] + pre_edge_w;
            }
            if (out_degree[pre] == 0) {
                pq.push({first_edge_w[pre], pushed_order, pre});
                pushed_order++;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << max_len[i] << ' ' << ans[i] << '\n';
    }

    return 0;
}