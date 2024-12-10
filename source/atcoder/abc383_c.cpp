// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<int>> bfs(vector<string> &room)
{
    int h = room.size();
    int w = room[0].size();

    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};

    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pii> q;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (room[r][c] == 'H') {
                dist[r][c] = 0;
                q.push({r, c});
            }
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                continue;
            }
            if (room[nr][nc] == '#') {
                continue;
            }
            if (dist[nr][nc] != -1) {
                continue;
            }
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }

    return dist;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int h, w, d;
    cin >> h >> w >> d;
    vector<string> room(h);
    for (int i = 0; i < h; i++) {
        cin >> room[i];
    }

    vector<vector<int>> dist = bfs(room);
    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (dist[i][j] != -1 && dist[i][j] <= d) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}