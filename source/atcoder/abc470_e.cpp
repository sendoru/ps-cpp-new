// #include "atcoder/all"
#pragma GCC optimize("O3")
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

    int n, l;
    cin >> n >> l;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<vector<ld>>> dp(l + 1, vector<vector<ld>>(n + 1, vector<ld>(n + 1, -1)));

    function<ld(int, int, int)> dfs = [&](int life, int remain, int know) -> ld {
        if (life <= 0 || remain <= 0 || know < 0 || know > remain) {
            return 0;
        }
        if (dp[life][remain][know] >= -0.5) {
            return dp[life][remain][know];
        }
        ld &res = dp[life][remain][know] = 0;
        int total = 2 * remain - know;
        if (total <= 0) {
            return res;
        }
        if (total == 1) {
            return res = 1;
        }

        ld p1 = (ld)know / total;
        ld p2 = (ld)(total - know) / total * (1) / (total - 1);
        ld p3 = (ld)(total - know) / total * (total - know - 2) / (total - 1);
        ld p4 = (ld)(total - know) / total * (know) / (total - 1);

        // cout << p1 + p2 + p3 + p4 << endl;

        if (remain > 0 && know > 0)
            res += p1 * (1 + dfs(life, remain - 1, know - 1));
        if (remain > 0)
            res += p2 * (1 + dfs(life, remain - 1, know));
        if (life > 1)
            res += p3 * dfs(life - 1, remain, know + 2);
        if (life > 1 && remain > 0)
            res += p4 * (1 + dfs(life - 1, remain - 1, know));

        return res;
    };

    ll sum_a = accumulate(a.begin(), a.end(), 0ll);
    cout << fixed << setprecision(10) << dfs(l, n, 0) * sum_a / n;

    return 0;
}