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
int dp[1647][1647][5][3];

int solve(int l, int r, int c, int q) {
    if (l > r) {
        return c == 0 ? 0 : 1;
    }
    if (dp[l][r][c][q] != -1) {
        return dp[l][r][c][q];
    }

    int &res = dp[l][r][c][q] = 0;
    string &cur_s = ss[q];

    if (c == 0) {
        if (q == 2) {
            res |= !solve(l, r, 0, 0);
            res |= !solve(l, r, 0, 1);
        }
        if (cur_s[l] != '?') {
            res |= solve(l + 1, r, cur_s[l] - '0' + 1, q);
        }
        if (cur_s[r] != '?') {
            res |= solve(l, r - 1, cur_s[r] - '0' + 3, q);
        }
        return res;
    }

    res |= !solve(l, r, 0, q);

    if (cur_s[l] != '?' && c == (cur_s[l] - '0' + 1)) {
        res |= solve(l + 1, r, cur_s[l] - '0' + 1, q);
    }
    if (cur_s[r] != '?' && c == (cur_s[r] - '0' + 3)) {
        res |= solve(l, r - 1, cur_s[r] - '0' + 3, q);
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(int), -1);

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
        ss[0][pos] = '0';
        ss[1][pos] = '1';
    }

    int ans = solve(0, s.size() - 1, 0, 2 * (!q_pos.empty()));
    cout << ans;

    return 0;
}