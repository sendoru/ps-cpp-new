// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<array<int, 2>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<string> board(n);
    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }
    vector<vector<bool>> visited(n, vector<bool>(n));
    vector<int> ans;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == '0' || visited[r][c])
                continue;
            int cnt = 0;
            queue<pii> q;
            q.push({r, c});
            visited[r][c] = true;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                cnt++;
                for (auto [dx, dy] : dir) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                        continue;
                    if (board[nx][ny] == '0' || visited[nx][ny])
                        continue;
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
            ans.push_back(cnt);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << '\n';
    }

    return 0;
}