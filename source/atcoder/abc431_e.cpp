// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int h, w;
        cin >> h >> w;
        vector<string> grid(h);
        for (int i = 0; i < h; i++) {
            cin >> grid[i];
        }
        // 칸 (r, c)에 방향 dir로 빛이 들어오도록 하도록 하는 최소 변경 횟수
        vector<vector<vector<int>>> dist(h, vector<vector<int>>(w, vector<int>(4, 1e9)));
        deque<tuple<int, int, int>> dq;
        dq.push_back({0, 0, 1});
        dist[0][0][1] = 0;
        while (!dq.empty()) {
            auto [r, c, dir] = dq.front();
            dq.pop_front();
            if (grid[r][c] == 'A') {
                for (int nd = 0; nd < 4; nd++) {
                    int nr = r + dr[nd];
                    int nc = c + dc[nd];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                        continue;
                    }
                    if (dir == nd) {
                        if (dist[nr][nc][nd] > dist[r][c][dir]) {
                            dq.push_front({nr, nc, nd});
                            dist[nr][nc][nd] = dist[r][c][dir];
                        }
                    } else {
                        if (dist[nr][nc][nd] > dist[r][c][dir] + 1) {
                            dq.push_back({nr, nc, nd});
                            dist[nr][nc][nd] = dist[r][c][dir] + 1;
                        }
                    }
                }
            } else if (grid[r][c] == 'B') {
                for (int nd = 0; nd < 4; nd++) {
                    int nr = r + dr[nd];
                    int nc = c + dc[nd];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                        continue;
                    }
                    if ((dir == 1 && nd == 0) || (dir == 0 && nd == 1) || (dir == 2 && nd == 3) || (dir == 3 && nd == 2)) {
                        if (dist[nr][nc][nd] > dist[r][c][dir]) {
                            dq.push_front({nr, nc, nd});
                            dist[nr][nc][nd] = dist[r][c][dir];
                        }
                    } else {
                        if (dist[nr][nc][nd] > dist[r][c][dir] + 1) {
                            dq.push_back({nr, nc, nd});
                            dist[nr][nc][nd] = dist[r][c][dir] + 1;
                        }
                    }
                }
            } else if (grid[r][c] == 'C') {
                for (int nd = 0; nd < 4; nd++) {
                    int nr = r + dr[nd];
                    int nc = c + dc[nd];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                        continue;
                    }
                    if ((dir == 1 && nd == 2) || (dir == 0 && nd == 3) || (dir == 2 && nd == 1) || (dir == 3 && nd == 0)) {
                        if (dist[nr][nc][nd] > dist[r][c][dir]) {
                            dq.push_front({nr, nc, nd});
                            dist[nr][nc][nd] = dist[r][c][dir];
                        }
                    } else {
                        if (dist[nr][nc][nd] > dist[r][c][dir] + 1) {
                            dq.push_back({nr, nc, nd});
                            dist[nr][nc][nd] = dist[r][c][dir] + 1;
                        }
                    }
                }
            }
        }
        int ans = 1e9;
        if (grid[h - 1][w - 1] == 'A') {
            ans = min(ans, dist[h - 1][w - 1][1]);
            ans = min(ans, dist[h - 1][w - 1][0] + 1);
            ans = min(ans, dist[h - 1][w - 1][2] + 1);
        } else if (grid[h - 1][w - 1] == 'B') {
            ans = min(ans, dist[h - 1][w - 1][0]);
            ans = min(ans, dist[h - 1][w - 1][1] + 1);
            ans = min(ans, dist[h - 1][w - 1][2] + 1);
        } else if (grid[h - 1][w - 1] == 'C') {
            ans = min(ans, dist[h - 1][w - 1][2]);
            ans = min(ans, dist[h - 1][w - 1][0] + 1);
            ans = min(ans, dist[h - 1][w - 1][1] + 1);
        }

        cout << ans << '\n';
    }

    return 0;
}