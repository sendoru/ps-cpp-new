// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(vector<string> &s, int start_move) {
    ll r = s.size(), c = s[0].size();
    int dr[] = {1, 0, -1, 0};
    int dc[] = {0, 1, 0, -1};

    pii start = {0, 0};
    pii end = {0, 0};
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < s[i].size(); j++) {
            if (s[i][j] == 'S') {
                start = {i, j};
            }
            if (s[i][j] == 'G') {
                end = {i, j};
            }
        }
    }

    vector<vector<array<int, 2>>> dists(r, vector<array<int, 2>>(c, {MOD1, MOD1}));
    dists[start.first][start.second][1 - start_move] = 0;
    queue<array<int, 3>> q;
    q.push({start.first, start.second, 1 - start_move});
    while (!q.empty()) {
        auto [cr, cc, move] = q.front();
        q.pop();
        int next_move = 1 - move;
        for (int d = next_move; d < 4; d += 2) {
            int nr = cr + dr[d];
            int nc = cc + dc[d];
            if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                continue;
            }
            if (s[nr][nc] == '#') {
                continue;
            }
            if (dists[nr][nc][next_move] != MOD1) {
                continue;
            }
            dists[nr][nc][next_move] = dists[cr][cc][move] + 1;
            q.push({nr, nc, next_move});
        }
    }

    return min(dists[end.first][end.second][0], dists[end.first][end.second][1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int r, c;
    cin >> r >> c;
    vector<string> s(r);
    for (int i = 0; i < r; i++) {
        cin >> s[i];
    }
    ll ans = min(solve(s, 0), solve(s, 1));
    if (ans == MOD1) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}