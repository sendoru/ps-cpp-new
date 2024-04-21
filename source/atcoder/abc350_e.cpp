#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll n, a, x, y;
ld solve(map<ll, ld> &dp, ll n)
{
    if (n == 0) {
        return 0;
    }
    if (dp.find(n) != dp.end()) {
        return dp[n];
    }
    ld cost_expected_op_1 = x + solve(dp, n / a);
    // 1/6 + 1/6^2 + ... = 1/5
    ld cost_expected_op_2 = (6.l / 5) * y;
    for (int i = 2; i <= 6; i++) {
        cost_expected_op_2 += solve(dp, n / i) / 5;
    }

    return dp[n] = min(cost_expected_op_1, cost_expected_op_2);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> a >> x >> y;

    // perform two operations:
    // 1. pay cost x and n = floor(n / a)
    // 2. pay cost y and roll the dice, n = floor(n / b) where b is the number
    // on the dice find the minimum expected cost to reach 0

    map<ll, ld> dp;
    cout << fixed << setprecision(10) << solve(dp, n) << '\n';

    return 0;
}