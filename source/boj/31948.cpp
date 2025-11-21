// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

string ss[3];
int dp[1647][1647][3];

int solve(int l, int r, int q) {
    if (l > r) {
        return 0;
    }
    if (dp[l][r][q] != -1) {
        return dp[l][r][q];
    }

    int &res = dp[l][r][q] = 1;
    string &cur_s = ss[q];

    if (q == 2) {
        res &= solve(l, r, 0);
        if (res == 0) {
            return res = 1;
        }
        res &= solve(l, r, 1);
        if (res == 0) {
            return res = 1;
        }
    }

    for (int i = l; i <= r; i++) {
        if ((i == l && cur_s[i] != '?') || (cur_s[i] == cur_s[i - 1])) {
            res &= solve(i + 1, r, q);
        } else {
            break;
        }
        if (res == 0) {
            return res = 1;
        }
    }
    for (int i = r; i >= l; i--) {
        if ((i == r && cur_s[i] != '?') || (cur_s[i] == cur_s[i + 1])) {
            res &= solve(l, i - 1, q);
        } else {
            break;
        }
        if (res == 0) {
            return res = 1;
        }
    }

    res ^= 1;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(int), -1);

    string s;
    cin >> s;

    vector<int> q_pos;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '?') {
            q_pos.push_back(i);
        }
    }

    for (int i = 0; i < 3; i++) {
        ss[i] = s;
    }

    for (int i = 0; i < q_pos.size(); i++) {
        int pos = q_pos[i];
        for (int j = 0; j < 3; j++) {
            ss[0][pos] = '0';
            ss[1][pos] = '1';
        }
    }

    int ans = solve(0, s.size() - 1, 2 * (!q_pos.empty()));
    cout << ans;

    return 0;
}