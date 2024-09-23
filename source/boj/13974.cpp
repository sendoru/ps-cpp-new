// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// O(n^3) matrix chain multiplication-ish
ll solve_naive(vector<ll> &v) {
    vector<vector<ll>> dp(v.size(), vector<ll>(v.size(), LLONG_MAX));
    vector<ll> sum(v.size());
    sum[0] = v[0];
    for (int i = 1; i < v.size(); i++) {
        sum[i] = sum[i - 1] + v[i];
    }

    for (int i = 0; i < v.size(); i++) {
        dp[i][i] = 0;
    }
    for (int end = 1; end < v.size(); end++) {
        for (int start = end - 1; start >= 0; start--) {
            for (int mid = start; mid < end; mid++) {
                ll range_sum = sum[end] - (start == 0 ? 0 : sum[start - 1]);
                dp[start][end] =
                    min(dp[start][end],
                        dp[start][mid] + dp[mid + 1][end] + range_sum);
            }
        }
    }

    return dp[0][v.size() - 1];
}

// O(n^2)
ll solve(vector<ll> &v) {
    vector<vector<ll>> dp(v.size(), vector<ll>(v.size(), LLONG_MAX));
    // split[i][j] = k means that the optimal split point for range [i, j] is k
    vector<vector<int>> split(v.size(), vector<int>(v.size()));
    vector<ll> sum(v.size());
    sum[0] = v[0];
    for (int i = 1; i < v.size(); i++) {
        sum[i] = sum[i - 1] + v[i];
    }

    for (int i = 0; i < v.size(); i++) {
        dp[i][i] = 0;
        split[i][i] = i;
    }
    for (int len = 2; len <= v.size(); len++) {
        for (int start = 0; start + len <= v.size(); start++) {
            int end = start + len - 1;
            for (int mid = split[start][end - 1]; mid <= split[start + 1][end] && mid < end; mid++) {
                ll range_sum = sum[end] - (start == 0 ? 0 : sum[start - 1]);
                if (dp[start][mid] + dp[mid + 1][end] + range_sum < dp[start][end]) {
                    dp[start][end] = dp[start][mid] + dp[mid + 1][end] + range_sum;
                    split[start][end] = mid;
                }
            }
        }
    }

    return dp[0][v.size() - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    int t = 50;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 1000);
    while (t--) {
        int n = 200;
        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = dis(gen);
        }

        ll ans1 = solve_naive(v);
        ll ans2 = solve(v);
        if (ans1 != ans2) {
            cout << "Mismatched: " << ans1 << ' ' << ans2 << '\n';
            for (int i = 0; i < n; i++) {
                cout << v[i] << ' ';
            }
            cout << '\n';
            break;
        }
    }
    cout << "Passed" << '\n';
#else
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        cout << solve(v) << '\n';
    }
#endif

    return 0;
}