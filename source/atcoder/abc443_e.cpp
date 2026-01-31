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

    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
        c--;
        vector<string> s(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        vector<int> last_wall(n, -1);
        for (int j = 0; j < n; j++) {
            for (int i = n - 1; i >= 0; i--) {
                if (s[i][j] == '#') {
                    last_wall[j] = i;
                    break;
                }
            }
        }
        vector<vector<array<int, 2>>> visited(n, vector<array<int, 2>>(n, {0, 0}));
        vector<pii> dirs = {{-1, -1}, {-1, 0}, {-1, 1}};
        queue<array<int, 3>> q;
        q.push({n - 1, c, 1});
        while (!q.empty()) {
            auto [x, y, breakable] = q.front();
            q.pop();
            for (auto [dr, dc] : dirs) {
                int nr = x + dr;
                int nc = y + dc;
                if (0 <= nr && nr < n && 0 <= nc && nc < n) {
                    bool n_breakable = (breakable && dc == 0) || (nr >= last_wall[nc]);
                    if (s[nr][nc] == '.') {
                        if (visited[nr][nc][n_breakable] == 0) {
                            visited[nr][nc][n_breakable] = 1;
                            q.push({nr, nc, n_breakable});
                        }
                    } else {
                        if (n_breakable == 1 && visited[nr][nc][n_breakable] == 0) {
                            visited[nr][nc][n_breakable] = 1;
                            q.push({nr, nc, n_breakable});
                        }
                    }
                }
            }
        }

        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            if (visited[0][i][0] == 1 || visited[0][i][1] == 1) {
                ans[i] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}