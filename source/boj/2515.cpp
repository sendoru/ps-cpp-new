#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, s;
    cin >> n >> s;
    vector<pll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    sort(v.begin(), v.end());

    vector<pll> dp(n);
    // i번째 그림을 보이게 할 경우
    dp[0].first = v[0].second;
    // i번째 그림을 보이지 않게 할 경우
    dp[0].second = 0;

    for (int i = 1; i < n; i++) {
        // i번째 그림을 보이게 하고 팔 수 있으려면
        // 그 앞에 있는 그림은 높이가 v[i].first - s 이하여야 한다.
        // 이분탐색
        auto iter = upper_bound(v.begin(), v.begin() + i, pll(v[i].first - s, INT64_MAX));
        if (iter != v.begin()) {
            iter--;
            dp[i].first = v[i].second + max(dp[iter - v.begin()].first, dp[iter - v.begin()].second);
        } else {
            dp[i].first = v[i].second;
        }

        dp[i].second = max(dp[i - 1].first, dp[i - 1].second);
    }

    cout << max(dp[n - 1].first, dp[n - 1].second) << '\n';

    return 0;
}