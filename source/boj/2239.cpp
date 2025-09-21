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

    vector<string> board(9);
    for (int i = 0; i < 9; i++) {
        cin >> board[i];
    }

    function<bool(int, int, char)> can_place = [&](int r, int c, char val) -> bool {
        for (int i = 0; i < 9; i++) {
            if (board[r][i] == val)
                return false;
            if (board[i][c] == val)
                return false;
        }
        for (int i = (r / 3) * 3; i < (r / 3) * 3 + 3; i++) {
            for (int j = (c / 3) * 3; j < (c / 3) * 3 + 3; j++) {
                if (board[i][j] == val)
                    return false;
            }
        }
        return true;
    };

    function<bool(int)> dfs = [&](int idx) -> bool {
        if (idx == 81)
            return true;
        int r = idx / 9;
        int c = idx % 9;
        if (board[r][c] != '0') {
            return dfs(idx + 1);
        } else {
            for (char val = '1'; val <= '9'; val++) {
                if (can_place(r, c, val)) {
                    board[r][c] = val;
                    if (dfs(idx + 1))
                        return true;
                    board[r][c] = '0';
                }
            }
            return false;
        }
    };

    dfs(0);
    for (int i = 0; i < 9; i++) {
        cout << board[i] << "\n";
    }

    return 0;
}