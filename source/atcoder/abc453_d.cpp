// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> dr = {1, -1, 0, 0};
vector<int> dc = {0, 0, 1, -1};
vector<char> dir = {'D', 'U', 'R', 'L'};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    array<int, 2> s, g;
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'S') {
                s = {i, j};
            } else if (grid[i][j] == 'G') {
                g = {i, j};
            }
        }
    }

    vector<vector<array<int, 4>>> dist(h, vector<array<int, 4>>(w, {MOD9, MOD9, MOD9, MOD9}));
    vector<vector<array<array<int, 3>, 4>>> prev(h, vector<array<array<int, 3>, 4>>(w));

    // x, y, dir
    queue<array<int, 3>> que;
    for (int i = 0; i < 4; i++) {
        dist[s[0]][s[1]][i] = 0;
        que.push({s[0], s[1], i});
    }

    while (!que.empty()) {
        auto [r, c, pd] = que.front();
        que.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w || grid[nr][nc] == '#') {
                continue;
            }
            if (grid[r][c] == 'o' && pd != d) {
                continue;
            }
            if (grid[r][c] == 'x' && pd == d) {
                continue;
            }
            if (dist[nr][nc][d] > dist[r][c][pd] + 1) {
                dist[nr][nc][d] = dist[r][c][pd] + 1;
                prev[nr][nc][d] = {r, c, pd};
                que.push({nr, nc, d});
            }
        }
    }

    bool found = false;
    vector<array<int, 3>> path;
    for (int d = 0; d < 4; d++) {
        if (dist[g[0]][g[1]][d] < MOD9) {
            found = true;
            int r = g[0], c = g[1];
            while (!(r == s[0] && c == s[1])) {
                auto &[pr, pc, pd] = prev[r][c][d];
                path.push_back({r, c, d});
                r = pr;
                c = pc;
                d = pd;
            }
            path.push_back({s[0], s[1], d});
            reverse(path.begin(), path.end());
            break;
        }
    }

    if (found) {
        cout << "Yes\n";
        string ans;
        for (int i = 1; i < (int)path.size(); i++) {
            int cdr = path[i][0] - path[i - 1][0];
            int cdc = path[i][1] - path[i - 1][1];
            for (int d = 0; d < 4; d++) {
                if (cdr == dr[d] && cdc == dc[d]) {
                    ans += dir[d];
                    break;
                }
            }
        }
        cout << ans << '\n';
    } else {
        cout << "No";
    }

    return 0;
}