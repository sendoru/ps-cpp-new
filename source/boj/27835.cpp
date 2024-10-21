// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
vector<vector<double>> dp;
ll r_max, h_max, n_max;

double solve(ll r, double h, ll n)
{
    if (n == 0) {
        return 0;
    }
    // if (n == 1) {
    //     return (1 + h) / 2.;
    // }
    if (dp[n][r] != -1) {
        return dp[n][r];
    }
    double &ret = dp[n][r];

    ret = 0;
    // (r_max - r) / r_max의 확률로 r+1 ~ r_max를 뽑게 되고
    // 이때 뽑은 건 일단 버려야 된다
    ret += (double)(r_max - r) / r_max * solve(r, h, n - 1);
    // 나머지 1, ... r을 뽑는 경우에 대해서
    for (int j = 1; j <= r; j++) {
        // 뽑은 걸 버리는 것 solve(r, h, n - 1)
        // 뽑은 걸 버리지 않는 것 solve(i, h, n - 1)
        // 중 최선을 선택
        double skip = solve(r, h, n - 1);
        double not_skip = solve(j, h, n - 1);
        double diff = skip - not_skip;
        diff = min(diff, (double)h_max);
        diff = max(diff, 0.);
        // 뽑은 것의 높이가 diff 이하면 skip, 아니면 not_skip
        ret += (1 / (double)r_max) * (int)diff / h_max * skip;
        ret += (1 / (double)r_max) * (h_max - (int)diff) / h_max * (not_skip + (h_max + 1 + (int)diff) / 2.);
    }

    return ret;
}

double solve_bottom_up(ll r, double h, ll n)
{
    vector<vector<double>> dp(n + 1, vector<double>(r + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= r; j++) {
            double &ret = dp[i][j];
            ret += (double)(r_max - j) / r_max * dp[i - 1][j];
            for (int k = 1; k <= j; k++) {
                double skip = dp[i - 1][j];
                double not_skip = dp[i - 1][k];
                double diff = skip - not_skip;
                diff = min(diff, (double)h_max);
                diff = max(diff, 0.);
                ret += (1 / (double)r_max) * (int)diff / h_max * skip;
                ret += (1 / (double)r_max) * (h_max - (int)diff) / h_max * (not_skip + (h_max + 1 + (int)diff) / 2.);
            }
        }
    }
    return *max_element(dp[n].begin(), dp[n].end());
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll r;
        double h;
        ll n;
        cin >> r >> h >> n;
        r_max = r;
        h_max = h;
        n_max = n;
        dp = vector<vector<double>>(n + 1, vector<double>(r + 1, -1));
        double ans = 0;
        // for (int i = 1; i <= r; i++) {
        //     ans = max(ans, solve(i, h, n));
        // }
        cout << fixed << setprecision(12) << solve_bottom_up(r, h, n) << '\n';
    }

    return 0;
}