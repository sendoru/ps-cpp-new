// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<array<ll, 2>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
ll cnts[401][401][201];
bool vistied[401][401][201];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll xs, ys, t;
    cin >> xs >> ys >> t;
    ll xh, yh;
    cin >> xh >> yh;

    // move xs, ys to (200, 200)
    ll off_x = 200 - xs;
    ll off_y = 200 - ys;
    xs += off_x;
    ys += off_y;
    xh += off_x;
    yh += off_y;

    vector<vector<bool>> blocked(401, vector<bool>(401, false));
    ll n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        x += off_x;
        y += off_y;
        if (x < 0 || x > 400 || y < 0 || y > 400) {
            continue;
        }
        blocked[x][y] = true;
    }

    vistied[xs][ys][0] = true;
    cnts[xs][ys][0] = 1;
    queue<array<ll, 3>> q;
    q.push({xs, ys, 0});
    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop();

        if (x == xh && y == yh) {
            continue;
        }

        if (d == t) {
            continue;
        }

        for (auto [dx, dy] : dir) {
            ll nx = x + dx;
            ll ny = y + dy;
            assert(nx >= 0 && nx <= 400 && ny >= 0 && ny <= 400);

            if (blocked[nx][ny]) {
                continue;
            }

            cnts[nx][ny][d + 1] += cnts[x][y][d];
            cnts[nx][ny][d + 1] %= MOD1;
            if (!vistied[nx][ny][d + 1]) {
                vistied[nx][ny][d + 1] = true;
                q.push({nx, ny, d + 1});
            }
        }
    }

    ll ans = 0;
    if (xh < 0 || xh > 400 || yh < 0 || yh > 400) {
        cout << 0 << "\n";
        return 0;
    }
    for (int d = 0; d <= t; d++) {
        ans += cnts[xh][yh][d];
        ans %= MOD1;
    }
    cout << ans << "\n";

    return 0;
}