// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> visited(n, vector<int>(m, -1));
    vector<int> area_size;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1' || visited[i][j] != -1)
                continue;

            int area_id = area_size.size();
            int size = 0;
            queue<pii> q;
            q.push({i, j});
            visited[i][j] = area_id;
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                size++;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                        continue;
                    if (grid[nr][nc] == '1' || visited[nr][nc] != -1)
                        continue;
                    visited[nr][nc] = area_id;
                    q.push({nr, nc});
                }
            }
            area_size.push_back(size);
        }
    }

    vector<string> ans = grid;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '0')
                continue;

            vector<int> adj_id;
            for (int d = 0; d < 4; d++) {
                int ni = i + dr[d];
                int nj = j + dc[d];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m)
                    continue;
                if (grid[ni][nj] == '0') {
                    int id = visited[ni][nj];
                    adj_id.push_back(id);
                }
            }
            sort(adj_id.begin(), adj_id.end());
            adj_id.erase(unique(adj_id.begin(), adj_id.end()), adj_id.end());
            int total_size = 1;
            for (int id : adj_id) {
                total_size += area_size[id];
            }
            ans[i][j] = (total_size % 10) + '0';
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}