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

    int n, x;
    cin >> n >> x;
    // score, cost, prob
    vector<vector<int>> scp(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> scp[i][0] >> scp[i][1] >> scp[i][2];
    }

    // dp[i]: i엔 남았을 때 가능한 최대 점수 기댓값
    vector<vector<double>> dp(x + 1, vector<double>(1 << n, -1));
    dp[0] = vector<double>(1 << n, 0);
    function<double(int, int)> solve_dp = [&](int money, int bitmask) {
        if (dp[money][bitmask] >= 0) {
            return dp[money][bitmask];
        }
        if (money <= 0) {
            return 0.0;
        }
        double &ans = dp[money][bitmask] = 0;
        for (int i = 0; i < n; i++) {
            if (money >= scp[i][1] && !(bitmask & (1 << i))) {
                int next_bistmask = bitmask | (1 << i);
                double prob = (double)scp[i][2] / 100;
                double score = scp[i][0];
                double next_score_solved = solve_dp(money - scp[i][1], next_bistmask);
                double next_score_not_solved = solve_dp(money - scp[i][1], bitmask);
                ans = max(ans, prob * (score + next_score_solved) + (1 - prob) * next_score_not_solved);
            }
        }
        return ans;
    };

    double ans = 0;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j < (1 << n); j++) {
            ans = max(ans, solve_dp(i, j));
        }
    }
    cout << fixed << setprecision(12) << ans << endl;

    return 0;
}