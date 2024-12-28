// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int k;
int dp[500'010][44];
string s, t;

// minimum edit distance
// to make s[:s_idx] to t[:s_idx+offset]
int solve(int s_idx, int offset)
{
    int t_idx = s_idx + offset;
    offset = offset + 21;
    if (offset < 0 || t_idx < 0) {
        return 1e9;
    }
    if (s_idx == 0 && offset == 0) {
        return 0;
    }
    if (s_idx == 0) {
        return t_idx;
    }
    if (t_idx == 0) {
        return s_idx;
    }
    if (dp[s_idx][offset] != -1) {
        return dp[s_idx][offset];
    }
    int &ret = dp[s_idx][offset];

    ret = 1e9;
    if (s[s_idx - 1] == t[t_idx - 1]) {
        ret = min(ret, solve(s_idx - 1, offset - 21));
    }
    else {
        ret = min(ret, solve(s_idx - 1, offset - 21) + 1);
    }
    if (offset > 0) {
        ret = min(ret, solve(s_idx, offset - 1 - 21) + 1);
    }
    if (offset < 44) {
        ret = min(ret, solve(s_idx - 1, offset + 1 - 21) + 1);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> k;
    cin >> s >> t;

    for (int i = 0; i < 500'010; i++) {
        for (int j = 0; j < 44; j++) {
            dp[i][j] = -1;
        }
    }
    int ans = solve(s.length(), t.length() - s.length());
    cout << (ans <= k ? "Yes" : "No") << endl;
    return 0;
}