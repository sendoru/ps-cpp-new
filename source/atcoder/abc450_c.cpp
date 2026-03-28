// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

array<int, 4> dr = {1, -1, 0, 0};
array<int, 4> dc = {0, 0, 1, -1};

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

    vector<vector<int>> cc_no(h, vector<int>(w, -1));
    int cc_cnt = 0;
    queue<array<int, 2>> q;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (cc_no[i][j] != -1 || grid[i][j] == '#') {
                continue;
            }
            cc_no[i][j] = cc_cnt;
            cc_cnt++;
            q.push({i, j});
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                        continue;
                    }
                    if (cc_no[nr][nc] != -1 || grid[nr][nc] == '#') {
                        continue;
                    }
                    cc_no[nr][nc] = cc_no[r][c];
                    q.push({nr, nc});
                }
            }
        }
    }

    vector<int> is_not_border(cc_cnt, 1);
    for (int i = 0; i < h; i++) {
        if (cc_no[i][0] != -1) {
            is_not_border[cc_no[i][0]] = 0;
        }
        if (cc_no[i][w - 1] != -1) {
            is_not_border[cc_no[i][w - 1]] = 0;
        }
    }
    for (int j = 0; j < w; j++) {
        if (cc_no[0][j] != -1) {
            is_not_border[cc_no[0][j]] = 0;
        }
        if (cc_no[h - 1][j] != -1) {
            is_not_border[cc_no[h - 1][j]] = 0;
        }
    }

    cout << accumulate(is_not_border.begin(), is_not_border.end(), 0);

    return 0;
}