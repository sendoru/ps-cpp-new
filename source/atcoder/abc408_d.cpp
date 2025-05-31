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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s_raw;
        cin >> s_raw;

        vector<int> s(n);
        for (int i = 0; i < n; i++) {
            s[i] = s_raw[i] - '0';
        }

        vector<int> pf_sum(n);
        pf_sum[0] = s[0];
        for (int i = 1; i < n; i++) {
            pf_sum[i] = pf_sum[i - 1] + s[i];
        }

        // i번째 글자까지 보고, i번째 글자가 j일 때 연속된 1의 구간을 최대 한 개로 만들기 위해 필요한 최소 filp 횟수
        vector<vector<int>> dp(n, vector<int>(2, MOD1));
        dp[0][0] = s[0];
        dp[0][1] = 1 - s[0];

        for (int i = 1; i < n; i++) {
            // i번째 글자가 0일 때
            // 일단 전부 0으로 만들기
            dp[i][0] = pf_sum[i];
            dp[i][0] = min(dp[i][0], dp[i - 1][0] + s[i]);
            dp[i][0] = min(dp[i][0], dp[i - 1][1] + s[i]);

            // i번째 글자가 1일 때
            dp[i][1] = pf_sum[i - 1] + (1 - s[i]);
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + (1 - s[i]));
        }

        cout << min(dp[n - 1][0], dp[n - 1][1]) << '\n';
    }

    return 0;
}