// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int dp[21][21][21][21];

int solve(int r1, int c1, int r2, int c2, const vector<string> &grid) {
    if (r1 > r2 || c1 > c2) {
        return 0;
    }
    if (dp[r1][c1][r2][c2] != -1) {
        return dp[r1][c1][r2][c2];
    }

    int &res = dp[r1][c1][r2][c2];
    // base case
    if (r1 == r2 && c1 == c2) {
        return res = (grid[r1][c1] == '.' ? 1 : 0);
    }

    array<int, 1024> next_g_mask = {};
    for (int r = r1; r <= r2; r++) {
        for (int c = c1; c <= c2; c++) {
            if (grid[r][c] == 'X') {
                continue;
            }
            int next_g = 0;
            next_g ^= solve(r1, c1, r - 1, c - 1, grid);
            next_g ^= solve(r1, c + 1, r - 1, c2, grid);
            next_g ^= solve(r + 1, c1, r2, c - 1, grid);
            next_g ^= solve(r + 1, c + 1, r2, c2, grid);
            next_g_mask[next_g] = 1;
        }
    }
    res = 0;
    while (next_g_mask[res]) {
        res++;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i < 21 * 21 * 21 * 21; i++) {
        *(&dp[0][0][0][0] + i) = -1;
    }

    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    for (int i = 0; i < r; i++) {
        cin >> grid[i];
    }

    int g = solve(0, 0, r - 1, c - 1, grid);
    if (g == 0) {
        cout << "Second";
    } else {
        cout << "First";
    }

    return 0;
}