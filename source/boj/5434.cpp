// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// bipartite matching
bool dfs(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &from, int curNode) {
    for (int nextNode : graph[curNode]) {
        if (from[nextNode] == -1) {
            from[nextNode] = curNode;
            return true;
        }
    }

    for (int nextNode : graph[curNode]) {
        if (visited[nextNode])
            continue;
        visited[nextNode] = true;
        if (dfs(graph, visited, from, from[nextNode])) {
            from[nextNode] = curNode;
            return true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, p;
        cin >> n >> p;
        vector<pll> ppl(p);
        vector<ll> vel(p);
        vector<pll> buttons(n);
        ld x1, y1, x2, y2, v;
        cin >> x1 >> y1 >> v;
        for (int i = 0; i < p; i++) {
            cin >> ppl[i].first >> ppl[i].second >> vel[i];
        }
        cin >> x2 >> y2;
        for (int i = 0; i < n; i++) {
            cin >> buttons[i].first >> buttons[i].second;
        }
        vector<vector<ld>> dist(p, vector<ld>(n));
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = sqrtl(powl(ppl[i].first - buttons[j].first, 2) + powl(ppl[i].second - buttons[j].second, 2)) / vel[i];
            }
        }

        // binary search
        ld l = 0, r = 2e18;
        ld ans = 2e18;
        for (int _ = 0; _ < 150; _++) {
            auto m = (l + r) / 2;
            vector<vector<int>> graph(p + n);
            for (int i = 0; i < p; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] <= m) {
                        graph[i].push_back(j + p);
                        graph[j + p].push_back(i);
                    }
                }
            }

            vector<int> from(p + n, -1);
            vector<bool> visited(p + n, false);
            int cnt = 0;
            for (int i = 0; i < p; i++) {
                fill(visited.begin(), visited.end(), false);
                if (dfs(graph, visited, from, i)) {
                    cnt++;
                }
            }

            if (cnt == n) {
                ans = min(ans, m);
                r = m;
            } else {
                l = m;
            }
        }

        cout << fixed << setprecision(12) << ans + sqrtl(powl(x1 - x2, 2) + powl(y1 - y2, 2)) / v << '\n';
    }

    return 0;
}