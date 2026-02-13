// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int combs[27][27];

bool check(vector<vector<int>> &ans) {
    int n = ans.size();
    set<int> sums;
    for (int move = 0; move < 1 << (2 * (n - 1)); move++) {
        int popcount = __builtin_popcount(move);
        if (popcount != n - 1) {
            continue;
        }
        int r = 0, c = 0;
        int sum = ans[0][0];
        for (int i = 0; i < 2 * (n - 1); i++) {
            if (move & (1 << i)) {
                c++;
            } else {
                r++;
            }
            sum += ans[r][c];
        }
        sums.insert(sum);
    }
    return sums.size() == combs[2 * (n - 1)][n - 1] && (*sums.end()) <= 6e6;
}

vector<vector<int>> solve(int n) {
    vector<vector<int>> ans(n, vector<int>(n, 0));

    for (int rpc = 1; rpc <= 2 * (n - 1); rpc++) {
        int cur = 0;
        for (int r = 0, c = rpc; r < n && c >= 0; r++, c--) {
            if (c < 0 || c >= n) {
                continue;
            }
            ans[r][c] = cur;
            cur += combs[rpc][r + 1];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i <= 26; i++) {
        combs[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            combs[i][j] = combs[i - 1][j - 1] + combs[i - 1][j];
        }
    }

#ifdef DEBUG
    for (int i = 2; i <= 13; i++) {
        auto ans = solve(i);
        assert(check(ans));
    }
    cout << "All test cases passed!" << endl;
#endif

    int n;
    cin >> n;
    auto ans = solve(n);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout << ans[r][c] << " ";
        }
        cout << "\n";
    }

    return 0;
}