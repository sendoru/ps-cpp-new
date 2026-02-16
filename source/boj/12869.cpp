// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int dists[61][61][61];

vector<array<int, 3>> moves = {
    {1, 3, 9},
    {1, 9, 3},
    {3, 1, 9},
    {3, 9, 1},
    {9, 1, 3},
    {9, 3, 1}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> hp(3);
    for (int i = 0; i < n; i++) {
        cin >> hp[i];
    }

    for (int i = 0; i <= 60; i++) {
        for (int j = 0; j <= 60; j++) {
            for (int k = 0; k <= 60; k++) {
                dists[i][j][k] = -1;
            }
        }
    }

    queue<array<int, 3>> q;
    q.push({hp[0], hp[1], hp[2]});
    dists[hp[0]][hp[1]][hp[2]] = 0;
    while (!q.empty()) {
        auto [a, b, c] = q.front();
        q.pop();
        for (auto &move : moves) {
            int na = max(0, a - move[0]);
            int nb = max(0, b - move[1]);
            int nc = max(0, c - move[2]);
            if (dists[na][nb][nc] == -1) {
                dists[na][nb][nc] = dists[a][b][c] + 1;
                q.push({na, nb, nc});
            }
        }
    }

    cout << dists[0][0][0];

    return 0;
}