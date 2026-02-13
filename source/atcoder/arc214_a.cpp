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

    int n;
    cin >> n;
    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (char c : s) {
            if (c == '?') {
                grid[i].push_back(-1);
            } else {
                grid[i].push_back(c - '0');
            }
        }
    }

    if (grid[0][0] == -1) {
        grid[0][0] = 0;
    }

    for (int rpc = 0; rpc <= 2 * (n - 1); rpc++) {
        set<int> vals;
        for (int r = 0, c = rpc; r < n && c >= 0; r++, c--) {
            if (c < 0 || c >= n) {
                continue;
            }
            if (grid[r][c] != -1) {
                vals.insert(grid[r][c]);
            }
        }
        if (vals.size() > 1) {
            cout << -1;
            return 0;
        }
        if (vals.empty()) {
            vals.insert(0);
        }
        for (int r = 0, c = rpc; r < n && c >= 0; r++, c--) {
            if (c < 0 || c >= n) {
                continue;
            }
            if (grid[r][c] == -1) {
                grid[r][c] = *vals.begin();
            }
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout << grid[r][c];
        }
        cout << "\n";
    }

    return 0;
}