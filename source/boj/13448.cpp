#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct problem {
    ll time;
    ll base_score;
    ll decay;
};

ll solve(vector<vector<ll>> &dp, vector<problem> &problems, int problem_no,
         int current_time, int time_limit)
{
    // checked all problems
    if (problem_no == problems.size()) {
        return 0;
    }

    ll &ret = dp[problem_no][current_time];
    if (ret != -1) {
        return ret;
    }

    // skip current problem
    if (current_time + problems[problem_no].time > time_limit) {
        ret = max(
            0ll, solve(dp, problems, problem_no + 1, current_time, time_limit));
    }
    else {
        ret = max(
            0ll, solve(dp, problems, problem_no + 1, current_time, time_limit));
        ret = max(ret,
                  solve(dp, problems, problem_no + 1,
                        current_time + problems[problem_no].time, time_limit) +
                      problems[problem_no].base_score -
                      problems[problem_no].decay *
                          (current_time + problems[problem_no].time));
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, t;
    cin >> n >> t;

    vector<problem> problems(n);

    for (int i = 0; i < n; i++) {
        cin >> problems[i].base_score;
    }
    for (int i = 0; i < n; i++) {
        cin >> problems[i].decay;
    }
    for (int i = 0; i < n; i++) {
        cin >> problems[i].time;
    }

    sort(problems.begin(), problems.end(),
         [](const problem &a, const problem &b) {
             return a.decay * b.time > b.decay * a.time;
         });

    // dp[i][j]: i번째 문제 이후를 고려했을 때, j시간이 주어졌을 때 얻을 수 있는
    // 최대 점수
    vector<vector<ll>> dp(n, vector<ll>(t + 100, -1));

    cout << max(0ll, solve(dp, problems, 0, 0, t)) << '\n';

    return 0;
}