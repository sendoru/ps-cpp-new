// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool check_range(vector<string> &board, int r, int c) {
    return r >= 0 && r < board.size() && c >= 0 && c < board[0].size();
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll r, c;
    cin >> r >> c;
    vector<string> board(r);
    pii start, cross;
    for (int i = 0; i < r; i++) {
        cin >> board[i];
        for (int j = 0; j < c; j++) {
            if (board[i][j] == '*') {
                start = {i, j};
            }
            if (board[i][j] == 'X') {
                cross = {i, j};
            }
        }
    }

    vector<vector<vector<int>>> dist(r, vector<vector<int>>(c, vector<int>(2, 1e9)));
    queue<tuple<int, int, int>> q;
    q.push({start.first, start.second, 0});
    dist[start.first][start.second][0] = 0;
    while (!q.empty()) {
        auto [cr, cc, is_cross] = q.front();
        int cur_dist = dist[cr][cc][is_cross];
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nr = cr + dr[i];
            int nc = cc + dc[i];
            int next_is_cross = is_cross;
            if (!check_range(board, nr, nc) || board[nr][nc] == 'X') {
                continue;
            }
            if (cr == cross.first - 1 && nr == cross.first && nc > cross.second) {
                continue;
            }
            if (cr == cross.first && nr == cross.first - 1 && cc > cross.second) {
                next_is_cross++;
                if (next_is_cross > 1) {
                    continue;
                }
            }

            if (dist[nr][nc][next_is_cross] > cur_dist + 1) {
                dist[nr][nc][next_is_cross] = cur_dist + 1;
                q.push({nr, nc, next_is_cross});
            }
        }
    }

    cout << dist[start.first][start.second][1] << '\n';
}

/*
6 7
....*..
.......
...X...
...X...
...X...
.......
*/