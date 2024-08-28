#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// undirected bipartite graph is given
// return the size of largest set of vertices such that
// no two vertices in the set are adjacent
int solve(vector<vector<int>> &adj_list, vector<int> &color)
{
    int n = adj_list.size();
    vector<int> from(n, -1);
    vector<bool> visited(n);

    function<bool(int)> dfs = [&](int cur) -> bool {
        for (int nxt : adj_list[cur]) {
            if (from[nxt] == -1) {
                from[nxt] = cur;
                return true;
            }
        }

        // re-wiring
        for (int nxt : adj_list[cur]) {
            if (visited[nxt]) {
                continue;
            }
            visited[nxt] = true;
            if (dfs(from[nxt])) {
                from[nxt] = cur;
                return true;
            }
        }

        return false;
    };

    int ans = n;
    for (int i = 0; i < n; i++) {
        if (color[i] == 1) {
            continue;
        }
        visited = vector<bool>(n, false);
        if (dfs(i)) {
            ans--;
        }
    }

    return ans;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        int n;
        cin >> n;
        if (cin.eof()) {
            break;
        }
        vector<pii> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i].first >> v[i].second;
        }

        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }

                if (abs(v[i].first - v[j].first) + abs(v[i].second - v[j].second) == 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        vector<int> color(n);
        for (int i = 0; i < n; i++) {
            color[i] = v[i].first + v[i].second & 1;
        }

        cout << solve(adj, color) << '\n';
    }

    return 0;
}