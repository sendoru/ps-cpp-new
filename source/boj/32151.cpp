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

    int n, m;
    cin >> n >> m;

    // i를 2진법으로 표현했을 때 1의 개수
    vector<int> one_cnt(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        int cur = i;
        while (cur > 0) {
            one_cnt[i] += cur & 1;
            cur >>= 1;
        }
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    reverse(a.begin(), a.end());

    // dp[i][j] = i번째 수까지 고려, 마지막 수가 j일때 차이가 1인 이웃한 수의 쌍의 개수의 최대값
    vector<vector<int>> dp(n, vector<int>(m + 1, -1));
    // max_dp[i] = i번째 수까지 고려할 때, 차이가 1인 이웃한 수의 쌍의 개수의 최대값
    vector<int> max_dp(n, -1);
    // max_idx[i] = i번째 수까지 고려할 때, 차이가 1인 이웃한 수의 쌍의 개수의 최대값을 가지는 j 중 가장 작은 j의 인덱스
    vector<int> max_idx(n, -1);
    vector<vector<int>> prev(n, vector<int>(m + 1, -1));

    // i = 0일때
    for (int j = 1; j <= m; j++) {
        if (one_cnt[j] == a[0]) {
            dp[0][j] = 0;
            max_dp[0] = 0;
            if (max_idx[0] == -1) {
                max_idx[0] = j;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        int max_prev_val = max_dp[i - 1];
        int max_prev_j = max_idx[i - 1];
        if (max_prev_j == -1) {
            break;
        }
        for (int j = 1; j <= m; j++) {
            if (one_cnt[j] != a[i]) {
                continue;
            }

            dp[i][j] = max_prev_val;
            prev[i][j] = max_prev_j;

            // j-1, j+1에서 오는 경우만 고려
            for (int d = -1; d <= 1; d += 2) {
                int nj = j + d;
                if (nj >= 1 && nj <= m && dp[i - 1][nj] != -1) {
                    int cand = dp[i - 1][nj] + 1;
                    if (cand > dp[i][j] || (cand == dp[i][j] && prev[i][j] > nj)) {
                        dp[i][j] = cand;
                        prev[i][j] = nj;
                    }
                }
            }

            // max_dp 업데이트
            if (dp[i][j] > max_dp[i]) {
                max_dp[i] = dp[i][j];
                max_idx[i] = j;
            }
        }
    }

    if (max_dp[n - 1] == -1) {
        cout << -1 << "\n";
        return 0;
    }

    cout << max_dp[n - 1] << "\n";
    int cur = max_idx[n - 1];
    vector<int> ans;
    for (int i = n - 1; i >= 0; i--) {
        ans.push_back(cur);
        cur = prev[i][cur];
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}