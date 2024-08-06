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

    int n, m, k;
    cin >> n >> m >> k;
    vector<pii> adj(n);
    for (int i = 0; i < n; i++) {
        cin >> adj[i].first >> adj[i].second;
        adj[i].first--;
        adj[i].second--;
    }

    vector<char> pattern(m);
    for (int i = 0; i < m; i++) {
        cin >> pattern[i];
    }

    vector<vector<int>> dist(n, vector<int>(m, INT32_MAX));
    vector<pair<int, int>> trace;
    int cur_dist = 0;
    int cur_node_dist;
    int cur = 0;
    while (true) {
        cur_node_dist = dist[cur][cur_dist % m];
        if (cur_node_dist != INT32_MAX) {
            break;
        }
        trace.push_back({cur, cur_dist % m});
        dist[cur][cur_dist % m] = cur_dist;
        if (pattern[cur_dist % m] == 'L') {
            cur = adj[cur].first;
        } else {
            cur = adj[cur].second;
        }
        cur_dist++;
    }

    if (m * k < trace.size()) {
        cout << trace[m * k].first + 1;
    } else {
        vector<pair<int, char>> cycle;
        for (int i = cur_node_dist; i < trace.size(); i++) {
            cycle.push_back(trace[i]);
        }
        ll mk = m * (ll)k;
        mk -= (trace.size() - cycle.size());
        mk %= cycle.size();
        cout << cycle[mk].first + 1;
    }

    return 0;
}