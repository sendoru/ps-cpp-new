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

    int r, c;
    cin >> r >> c;
    int n;
    cin >> n;
    vector<array<int, 4>> rects(n);
    for (int i = 0; i < n; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        rects[i] = {r1, c1, r2, c2};
    }

    vector<int> coords = {0, r, c};
    for (const auto &rect : rects) {
        coords.push_back(rect[0]);
        coords.push_back(rect[1]);
        coords.push_back(rect[2]);
        coords.push_back(rect[3]);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    r = lower_bound(coords.begin(), coords.end(), r) - coords.begin();
    c = lower_bound(coords.begin(), coords.end(), c) - coords.begin();
    for (auto &rect : rects) {
        rect[0] = lower_bound(coords.begin(), coords.end(), rect[0]) - coords.begin();
        rect[1] = lower_bound(coords.begin(), coords.end(), rect[1]) - coords.begin();
        rect[2] = lower_bound(coords.begin(), coords.end(), rect[2]) - coords.begin();
        rect[3] = lower_bound(coords.begin(), coords.end(), rect[3]) - coords.begin();
    }

    vector<vector<int>> imos(r + 1, vector<int>(c + 1, 0));
    for (const auto &rect : rects) {
        imos[rect[0]][rect[1]] += 1;
        imos[rect[0]][rect[3]] -= 1;
        imos[rect[2]][rect[1]] -= 1;
        imos[rect[2]][rect[3]] += 1;
    }

    for (int i = 0; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            imos[i][j] += imos[i][j - 1];
        }
    }
    for (int j = 0; j <= c; j++) {
        for (int i = 1; i <= r; i++) {
            imos[i][j] += imos[i - 1][j];
        }
    }
    imos.pop_back();
    for (int i = 0; i < r; i++) {
        imos[i].pop_back();
    }

    int ans = 0;
    array<int, 4> dr = {1, -1, 0, 0}, dc = {0, 0, 1, -1};
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (imos[i][j] > 0) {
                continue;
            }
            ans++;
            queue<pii> q;
            q.push({i, j});
            imos[i][j] = 1;
            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = cr + dr[d];
                    int nc = cc + dc[d];
                    if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                        continue;
                    }
                    if (imos[nr][nc] > 0) {
                        continue;
                    }
                    imos[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}