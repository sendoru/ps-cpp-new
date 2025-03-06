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

    int n;
    cin >> n;
    vector<vector<vector<short>>> adj_list(2);
    adj_list[0].resize(n + 1);
    adj_list[1].resize(1234);
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        for (int j = 0; j < t; j++) {
            int r;
            cin >> r;
            adj_list[0][i].push_back(r);
            adj_list[1][r].push_back(i);
        }
    }
    vector<vector<short>> match(2);
    match[0].resize(n + 1);
    match[1].resize(1234);
    vector<vector<bool>> visited(2);
    visited[0].resize(n + 1);
    visited[1].resize(1234);

    function<bool(int, int)> dfs = [&](int node, int max_r) {
        if (node == -1)
            return true;
        for (int next : adj_list[0][node]) {
            if (next > max_r)
                continue;

            if (match[1][next] == -1) {
                match[1][next] = node;
                return true;
            }
        }
        for (int next : adj_list[0][node]) {
            if (next > max_r)
                continue;
            if (visited[1][next])
                continue;
            visited[1][next] = true;
            if (match[1][next] == -1 || dfs(match[1][next], max_r)) {
                match[1][next] = node;
                return true;
            }
        }
        return false;
    };

    int ans = 1234;

    int lo = 1, hi = 1234;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int match_cnt = 0;
        fill(match[0].begin(), match[0].end(), -1);
        fill(match[1].begin(), match[1].end(), -1);
        for (int i = 1; i <= n; i++) {
            fill(visited[0].begin(), visited[0].end(), false);
            fill(visited[1].begin(), visited[1].end(), false);
            if (dfs(i, mid))
                match_cnt++;
        }
        if (match_cnt == n) {
            ans = min(ans, mid);
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << ans + 1 << '\n';

    return 0;
}