// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll sum_dp[20][20][20][2], cnt_dp[20][20][20][2];

bool is_substring(const string &haystack, const string &needle) {
    int n_idx = 0;
    for (char c : haystack) {
        if (n_idx < (int)needle.size() && c == needle[n_idx]) {
            n_idx++;
        }
    }
    return n_idx == (int)needle.size();
}

ll solve(ll n) {
    if (n <= 0) {
        return 0;
    }
    fill(&sum_dp[0][0][0][0], &sum_dp[19][19][19][2], 0LL);
    fill(&cnt_dp[0][0][0][0], &cnt_dp[19][19][19][2], 0LL);
    string n_s = to_string(n);
    // dp[0][0][0][1] = 1;
    for (int i = 0; i < n_s[0] - '0'; i++) {
        sum_dp[1][i][1][0] = i;
        cnt_dp[1][i][1][0] = 1;
    }
    sum_dp[1][n_s[0] - '0'][1][1] = n_s[0] - '0';
    cnt_dp[1][n_s[0] - '0'][1][1] = 1;
    // 확인한 자릿수 갯수
    for (int i = 1; i < (int)n_s.size(); i++) {
        // 맨 뒷 자리가 j
        for (int j = 0; j <= 9; j++) {
            // 맨 뒤에 연속해서 오는 j의 개수가 k
            for (int k = 0; k <= i; k++) {
                // bounded?

                for (int d = 0; d <= 9; d++) {
                    int nj, nk;
                    if (d == j) {
                        nj = j;
                        nk = k + 1;
                    } else {
                        nj = d;
                        nk = 1;
                    }
                    cnt_dp[i + 1][nj][nk][0] += cnt_dp[i][j][k][0];
                    sum_dp[i + 1][nj][nk][0] += sum_dp[i][j][k][0];
                    if (nk == 1) {
                        sum_dp[i + 1][nj][nk][0] += cnt_dp[i][j][k][0] * d;
                    } else {
                        sum_dp[i + 1][nj][nk][0] += cnt_dp[i][j][k][0] * d * nk * nk;
                        sum_dp[i + 1][nj][nk][0] -= cnt_dp[i][j][k][0] * d * (nk - 1) * (nk - 1);
                    }

                    if (d < n_s[i] - '0') {
                        cnt_dp[i + 1][nj][nk][0] += cnt_dp[i][j][k][1];
                        sum_dp[i + 1][nj][nk][0] += sum_dp[i][j][k][1];
                        if (nk == 1) {
                            sum_dp[i + 1][nj][nk][0] += cnt_dp[i][j][k][1] * d;
                        } else {
                            sum_dp[i + 1][nj][nk][0] += cnt_dp[i][j][k][1] * d * nk * nk;
                            sum_dp[i + 1][nj][nk][0] -= cnt_dp[i][j][k][1] * d * (nk - 1) * (nk - 1);
                        }
                    } else if (d == n_s[i] - '0') {
                        cnt_dp[i + 1][nj][nk][1] += cnt_dp[i][j][k][1];
                        sum_dp[i + 1][nj][nk][1] += sum_dp[i][j][k][1];
                        if (nk == 1) {
                            sum_dp[i + 1][nj][nk][1] += cnt_dp[i][j][k][1] * d;
                        } else {
                            sum_dp[i + 1][nj][nk][1] += cnt_dp[i][j][k][1] * d * nk * nk;
                            sum_dp[i + 1][nj][nk][1] -= cnt_dp[i][j][k][1] * d * (nk - 1) * (nk - 1);
                        }
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            ans += sum_dp[n_s.size()][i][j][0] + sum_dp[n_s.size()][i][j][1];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a - 1) << "\n";

    return 0;
}