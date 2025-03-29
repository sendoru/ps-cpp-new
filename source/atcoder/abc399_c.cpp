// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        adj_list[s].push_back(e);
        adj_list[e].push_back(s);
    }

    vector<bool> visited(n, false);
    int cc_count = 0;
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int next : adj_list[node]) {
            if (!visited[next]) {
                dfs(next);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            cc_count++;
        }
    }

    int target = n - cc_count;
    cout << m - target << "\n";

    return 0;
}