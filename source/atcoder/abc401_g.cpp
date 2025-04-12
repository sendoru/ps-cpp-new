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
bool dfs(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &from, int curNode)
{
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pll> ppl(n);
    vector<pll> buttons(n);
    for (int i = 0; i < n; i++) {
        cin >> ppl[i].first >> ppl[i].second;
    }
    for (int i = 0; i < n; i++) {
        cin >> buttons[i].first >> buttons[i].second;
    }
    vector<vector<ld>> dist(n, vector<ld>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = sqrtl(powl(ppl[i].first - buttons[j].first, 2) + powl(ppl[i].second - buttons[j].second, 2));
        }
    }

    // binary search
    ld l = 0, r = 2e18;
    ld ans = 2e18;
    for (int _ = 0; _ < 150; _++) {
        auto m = (l + r) / 2;
        vector<vector<int>> graph(2 * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] <= m) {
                    graph[i].push_back(j + n);
                    graph[j + n].push_back(i);
                }
            }
        }

        vector<int> from(2 * n, -1);
        vector<bool> visited(2 * n, false);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            fill(visited.begin(), visited.end(), false);
            if (dfs(graph, visited, from, i)) {
                cnt++;
            }
        }

        if (cnt == n) {
            ans = min(ans, m);
            r = m;
        }
        else {
            l = m;
        }
    }

    cout << fixed << setprecision(12) << ans << endl;

    return 0;
}