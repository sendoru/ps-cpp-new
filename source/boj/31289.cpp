// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int dp[202][202][202];

int solve(int a, int b, int c)
{
    int abc_sum = a + b + c;
    int &ret = dp[a][b][c];
    if (ret != -1) {
        return ret;
    }
    ret = 0;
    if (abc_sum == 0) {
        return ret = 0;
    }
    int abc_xor = a ^ b ^ c;
    if (abc_xor != 0) {
        if ((a ^ abc_xor) <= a) {
            ret = max(ret, abc_sum - solve((a ^ abc_xor), b, c));
        }
        if ((b ^ abc_xor) <= b) {
            ret = max(ret, abc_sum - solve(a, (b ^ abc_xor), c));
        }
        if ((c ^ abc_xor) <= c) {
            ret = max(ret, abc_sum - solve(a, b, (c ^ abc_xor)));
        }
    }
    else {
        for (int i = 1; i <= a; i++) {
            ret = max(ret, abc_sum - solve(a - i, b, c));
        }
        for (int i = 1; i <= b; i++) {
            ret = max(ret, abc_sum - solve(a, b - i, c));
        }
        for (int i = 1; i <= c; i++) {
            ret = max(ret, abc_sum - solve(a, b, c - i));
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for (int i = 0; i < 202; i++) {
        for (int j = 0; j < 202; j++) {
            for (int k = 0; k < 202; k++) {
                dp[i][j][k] = -1;
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        int ans = solve(a, b, c);
        cout << 10000ll * ans << ' ' << 10000ll * (a + b + c - ans) << '\n';
    }

    return 0;
}