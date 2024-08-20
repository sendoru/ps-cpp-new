#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }
        vector<vector<int>> board(n, vector<int>(m));

        int k1;
        cin >> k1;
        vector<pii> queens(k1);
        for (int i = 0; i < k1; i++) {
            cin >> queens[i].first >> queens[i].second;
            queens[i].first--;
            queens[i].second--;
            board[queens[i].first][queens[i].second] = 2;
        }

        int k2;
        cin >> k2;
        vector<pii> knights(k2);
        for (int i = 0; i < k2; i++) {
            cin >> knights[i].first >> knights[i].second;
            knights[i].first--;
            knights[i].second--;
            board[knights[i].first][knights[i].second] = 2;
        }

        int k3;
        cin >> k3;
        vector<pii> pawns(k3);
        for (int i = 0; i < k3; i++) {
            cin >> pawns[i].first >> pawns[i].second;
            pawns[i].first--;
            pawns[i].second--;
            board[pawns[i].first][pawns[i].second] = 2;
        }

        vector<int> dr = {1, 1, 1, 0, 0, -1, -1, -1};
        vector<int> dc = {1, -1, 0, 1, -1, 1, -1, 0};

        for (int i = 0; i < queens.size(); i++) {
            for (int dir = 0; dir < 8; dir++) {
                for (int d = 1;; d++) {
                    int r = queens[i].first + d * dr[dir];
                    int c = queens[i].second + d * dc[dir];

                    if (r < 0 || r >= n || c < 0 || c >= m || board[r][c] == 2) {
                        break;
                    }
                    board[r][c] = 1;
                }
            }
        }

        dr = {-2, -2, -1, -1, 1, 1, 2, 2};
        dc = {-1, 1, -2, 2, -2, 2, -1, 1};
        for (int i = 0; i < knights.size(); i++) {
            for (int dir = 0; dir < 8; dir++) {
                int r = knights[i].first + dr[dir];
                int c = knights[i].second + dc[dir];
                if (r < 0 || r >= n || c < 0 || c >= m || board[r][c] == 2) {
                    continue;
                }
                board[r][c] = 1;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 0) {
                    ans++;
                }
            }
        }

        cout << ans << '\n';

        break;
    }

    return 0;
}