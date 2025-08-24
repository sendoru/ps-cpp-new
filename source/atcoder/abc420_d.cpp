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

    int h, w;
    cin >> h >> w;

    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    vector<int> start(3), goal(3);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'S') {
                start[0] = i;
                start[1] = j;
            }
            if (grid[i][j] == 'G') {
                goal[0] = i;
                goal[1] = j;
            }
        }
    }

    queue<vector<int>> q;
    q.push(start);
    vector<vector<vector<int>>> dist(h, vector<vector<int>>(w, vector<int>(2, 1e9)));
    dist[start[0]][start[1]][0] = 0;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int r = cur[0], c = cur[1], toggle = cur[2];
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                continue;
            }
            if (grid[nr][nc] == '#') {
                continue;
            }
            if (toggle == 0 && grid[nr][nc] == 'x') {
                continue;
            }
            if (toggle == 1 && grid[nr][nc] == 'o') {
                continue;
            }
            int ntoggle = toggle;
            if (grid[nr][nc] == '?') {
                ntoggle = 1 - toggle;
            }
            if (dist[nr][nc][ntoggle] != 1e9) {
                continue;
            }
            dist[nr][nc][ntoggle] = dist[r][c][toggle] + 1;
            q.push({nr, nc, ntoggle});
        }
    }

    int ans = min(dist[goal[0]][goal[1]][0], dist[goal[0]][goal[1]][1]);
    if (ans == 1e9) {
        ans = -1;
    }
    cout << ans << "\n";

    return 0;
}