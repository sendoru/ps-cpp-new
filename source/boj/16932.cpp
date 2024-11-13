// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> dr = {1, -1, 0, 0}, dc = {0, 0, 1, -1};

void paint(vector<vector<int>> &board, vector<vector<int>> &dest, pii start, int color) {
    int r = board.size(), c = board[0].size();
    queue<pii> q;
    q.push(start);
    dest[start.first][start.second] = color;
    while (!q.empty()) {
        auto [cr, cc] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = cr + dr[d], nc = cc + dc[d];
            if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                continue;
            }
            if (board[nr][nc] == 0 || dest[nr][nc] != 0) {
                continue;
            }
            dest[nr][nc] = color;
            q.push({nr, nc});
        }
    }
}

vector<vector<int>> paint_all(vector<vector<int>> &board) {
    int n = board.size(), m = board[0].size();
    int cur_color = 1;
    vector<vector<int>> colors(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 1 && colors[i][j] == 0) {
                paint(board, colors, {i, j}, cur_color);
                cur_color++;
            }
        }
    }
    return colors;
}

vector<int> get_cc_sizes(vector<vector<int>> &colors) {
    int n = colors.size(), m = colors[0].size();
    vector<int> cc_size;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (colors[i][j] == 0) {
                continue;
            }
            while (colors[i][j] >= cc_size.size()) {
                cc_size.push_back(0);
            }
            cc_size[colors[i][j]]++;
        }
    }
    return cc_size;
}

int get_max_joined_cc_size(vector<vector<int>> &colors) {
    int n = colors.size(), m = colors[0].size();
    auto cc_size = get_cc_sizes(colors);
    int ret = max(1, *max_element(cc_size.begin(), cc_size.end()));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (colors[i][j] != 0) {
                continue;
            }
            vector<int> adj_cc;
            for (int d = 0; d < 4; d++) {
                int ni = i + dr[d], nj = j + dc[d];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) {
                    continue;
                }
                adj_cc.push_back(colors[ni][nj]);
            }
            sort(adj_cc.begin(), adj_cc.end());
            adj_cc.erase(unique(adj_cc.begin(), adj_cc.end()), adj_cc.end());
            int cur_ans = 1;
            for (int cc : adj_cc) {
                cur_ans += cc_size[cc];
            }
            ret = max(ret, cur_ans);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    auto color = paint_all(board);
    auto ans = get_max_joined_cc_size(color);

    cout << ans << "\n";
    return 0;
}