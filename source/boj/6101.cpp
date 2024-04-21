#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    // dp[i][j] : i번째 원소까지 고려하고, 마지막 집합의 unique 원소가 j개일
    // 때의 비용
    vector<vector<ll>> dp(n, vector<ll>(min(m + 1, 250), LLONG_MAX / 4));
    vector<vector<int>> range_size(n,
                                   vector<int>(min(m + 1, 250), INT32_MAX / 4));

    // dp[i][j]에서 다음 원소 a[i + 1]을 추가할 때,
    // 1. 새로운 집합을 만드는 경우
    // dp[i + 1][1] = min(dp[i + 1][1], dp[i][j] + 1)
    // 2. 기존 집합에 추가하는 경우
    // 마지막 집합에 a[i + 1]이 있는 경우,
    // dp[i + 1][j] = min(dp[i + 1][j], dp[i][j])
    // 그렇지 않은 경우,
    // dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 2 * j + 1)

    dp[0][1] = 1;
    range_size[0][1] = 1;
    // 각 i에 대해 마지막 집합에 a[i]가 존재하는지 판별하기 위해,
    // last_appear[a[i]] = i로 설정
    vector<int> last_appear(m, -1);
    for (int i = 0; i < n - 1; i++) {
        last_appear[a[i]] = i;

        for (int j = 1; j < dp[0].size(); j++) {

            // 새로운 집합을 만드는 경우
            if (dp[i][j] + 1 < dp[i + 1][1]) {
                dp[i + 1][1] = dp[i][j] + 1;
                range_size[i + 1][1] = 1;
            }
        }

        for (int j = 1; j < dp[0].size(); j++) {
            // 기존 집합에 추가하는 경우
            if (last_appear[a[i + 1]] == -1 ||
                last_appear[a[i + 1]] <= i - range_size[i][j]) {
                if (j + 1 < dp[0].size() &&
                    dp[i][j] + 2 * j + 1 < dp[i + 1][j + 1]) {
                    dp[i + 1][j + 1] = dp[i][j] + 2 * j + 1;
                    range_size[i + 1][j + 1] = range_size[i][j] + 1;
                }
            }
            else {
                if (dp[i][j] < dp[i + 1][j]) {
                    dp[i + 1][j] = dp[i][j];
                    range_size[i + 1][j] = range_size[i][j] + 1;
                }
            }
        }
    }

    ll ans = LLONG_MAX;
    for (int j = 1; j < dp[0].size(); j++) {
        ans = min(ans, dp.back()[j]);
    }

    cout << ans;

    return 0;
}