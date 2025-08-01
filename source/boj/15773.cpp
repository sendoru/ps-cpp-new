// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve_pq(vector<pll> &ld) {
    ll n = ld.size();
    ll ans = 0, d_sum = 0;
    priority_queue<ll> pq;
    for (int i = 0; i < n; i++) {
        if (d_sum <= ld[i].first) {
            pq.push(ld[i].second);
            d_sum += ld[i].second;
        } else if (ld[i].second < pq.top()) {
            d_sum -= pq.top();
            pq.pop();
            pq.push(ld[i].second);
            d_sum += ld[i].second;
        }
        ans = max(ans, (ll)pq.size());
    }
    return ans;
}

ll solve_dp(vector<pll> &ld) {
    ll n = ld.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, INT64_MAX));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            if (dp[i - 1][j - 1] != INT64_MAX &&
                dp[i - 1][j - 1] <= ld[i - 1].first) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + ld[i - 1].second);
            }
        }
    }
    for (int i = n; i >= 0; i--) {
        if (dp.back()[i] != INT64_MAX) {
            return i;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<ll> dis(0, (ll)1e9);
    for (int _ = 0; _ < 5000; _++) {
        vector<pll> test(200);
        for (int i = 0; i < 50; i++) {
            test[i] = {dis(gen) * 100, dis(gen) + 1};
        }
        sort(test.begin(), test.end());
        ll ans = solve_pq(test);
        ll ans_dp = solve_dp(test);
        assert(ans == ans_dp);
    }
    cout << "Test passed!" << endl;
#endif

    int n;
    cin >> n;
    vector<pll> ld(n);
    for (int i = 0; i < n; i++) {
        cin >> ld[i].first >> ld[i].second;
    }
    sort(ld.begin(), ld.end(), [](auto &x, auto &y) {
        return x.first + x.second < y.first + y.second;
    });

    cout << solve_dp(ld);

    return 0;
}