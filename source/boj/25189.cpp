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
    pii s, e;
    cin >> s.first >> s.second >> e.first >> e.second;
    s.first--;
    s.second--;
    e.first--;
    e.second--;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<array<ll, 2>>> dist(n, vector<array<ll, 2>>(m, {(ll)1e12, (ll)1e12}));

    array<pii, 4> directions = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
    queue<array<int, 3>> q;
    q.push({s.first, s.second, 0});
    dist[s.first][s.second][0] = 0;
    while (!q.empty()) {
        auto [r, c, used] = q.front();
        q.pop();
        for (auto &[dr, dc] : directions) {
            int nr = r + dr * grid[r][c];
            int nc = c + dc * grid[r][c];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                continue;
            }
            if (dist[nr][nc][used] >= (ll)1e12) {
                dist[nr][nc][used] = dist[r][c][used] + 1;
                q.push({nr, nc, used});
            }
        }
        if (!used) {
            // to same end row
            int nr = e.first;
            int nc = c;
            if (dist[nr][nc][1] >= (ll)1e12) {
                dist[nr][nc][1] = dist[r][c][used] + 1;
                q.push({nr, nc, 1});
            }
            // to same end column
            nr = r;
            nc = e.second;
            if (dist[nr][nc][1] >= (ll)1e12) {
                dist[nr][nc][1] = dist[r][c][used] + 1;
                q.push({nr, nc, 1});
            }
        }
    }

    ll ans = min(dist[e.first][e.second][0], dist[e.first][e.second][1]);
    if (ans >= (ll)1e12) {
        ans = -1;
    }
    cout << ans;

    return 0;
}