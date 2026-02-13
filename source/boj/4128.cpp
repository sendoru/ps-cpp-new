// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

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

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int n;
    cin >> n;
    vector<array<int, 4>> rects(n);
    for (int i = 0; i < n; i++) {
        cin >> rects[i][0] >> rects[i][1] >> rects[i][2] >> rects[i][3];
    }

    vector<int> unique_vals;
    unique_vals.push_back(x1);
    unique_vals.push_back(x2);
    unique_vals.push_back(y1);
    unique_vals.push_back(y2);
    for (int i = 0; i < n; i++) {
        unique_vals.push_back(rects[i][0]);
        unique_vals.push_back(rects[i][1]);
        unique_vals.push_back(rects[i][2]);
        unique_vals.push_back(rects[i][3]);
    }
    sort(unique_vals.begin(), unique_vals.end());
    unique_vals.erase(unique(unique_vals.begin(), unique_vals.end()), unique_vals.end());

    auto get_compressed = [&](int val) {
        return (int)(lower_bound(unique_vals.begin(), unique_vals.end(), val) - unique_vals.begin());
    };

    x1 = get_compressed(x1);
    x2 = get_compressed(x2);
    y1 = get_compressed(y1);
    y2 = get_compressed(y2);
    if (x1 > x2)
        swap(x1, x2);
    if (y1 > y2)
        swap(y1, y2);

    for (int i = 0; i < n; i++) {
        rects[i][0] = get_compressed(rects[i][0]);
        rects[i][1] = get_compressed(rects[i][1]);
        rects[i][2] = get_compressed(rects[i][2]);
        rects[i][3] = get_compressed(rects[i][3]);
        if (rects[i][0] > rects[i][2])
            swap(rects[i][0], rects[i][2]);
        if (rects[i][1] > rects[i][3])
            swap(rects[i][1], rects[i][3]);
    }

    int sz = unique_vals.size();
    vector<vector<int>> grid(sz, vector<int>(sz, 0));
    for (int i = 0; i < n; i++) {
        for (int x = rects[i][0]; x < rects[i][2]; x++) {
            for (int y = rects[i][1]; y < rects[i][3]; y++) {
                if (x >= x1 && x < x2 && y >= y1 && y < y2) {
                    grid[x][y] = 1;
                }
            }
        }
    }
    for (int x = 0; x < sz; x++) {
        for (int y = 0; y < sz; y++) {
            if (x < x1 || x >= x2 || y < y1 || y >= y2) {
                grid[x][y] = 1;
            }
        }
    }

    int ans = 0;
    vector<pii> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<bool>> visited(sz, vector<bool>(sz, false));
    queue<pii> q;

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (grid[i][j] == 0 && !visited[i][j]) {
                q.push({i, j});
                visited[i][j] = true;
                while (!q.empty()) {
                    pii cur = q.front();
                    q.pop();
                    for (auto &dir : dirs) {
                        int nx = cur.x + dir.x;
                        int ny = cur.y + dir.y;
                        if (nx < 0 || nx >= sz || ny < 0 || ny >= sz) {
                            continue;
                        }
                        if (grid[nx][ny] == 0 && !visited[nx][ny]) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
                ans++;
            }
        }
    }

    cout << ans;

    return 0;
}