#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<pii> bfs(vector<vector<int>> &a, vector<vector<bool>> &visited, pii start)
{
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    int n = a.size();
    int m = a[0].size();
    vector<pii> ret;
    queue<pii> q;
    q.push(start);
    visited[start.first][start.second] = true;
    ret.push_back(start);
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc] && a[r][c] == a[nr][nc]) {
                q.push({nr, nc});
                visited[nr][nc] = true;
                ret.push_back({nr, nc});
            }
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    auto b = a;
    vector<vector<bool>> a_visited(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] - '0';
        }
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            b[i][j] = s[j] - '0';
        }
    }

    bool ans = true;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (a_visited[r][c]) {
                continue;
            }
            auto group = bfs(a, a_visited, {r, c});
            for (int i = 0; i < group.size(); i++) {
                if (b[group[0].first][group[0].second] != b[group[i].first][group[i].second]) {
                    ans = false;
                    break;
                }
            }
        }
    }

    cout << (ans ? "YES" : "NO") << '\n';

    return 0;
}