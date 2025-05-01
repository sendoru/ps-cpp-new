// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll dp[19][19][19][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int c;
    cin >> c;
    while (c--) {
        ll m, z, r;
        cin >> m >> z >> r;
        string max_s = to_string(m - 1), z_s = to_string(z);
        int max_len = max_s.length(), z_len = z_s.length();
        z_s = string(max_len - z_len, '0') + z_s;

        vector<int> max_v(max_len), z_v(max_len);
        for (int i = 0; i < max_len; i++) {
            max_v[i] = max_s[i] - '0';
            z_v[i] = z_s[i] - '0';
        }
        dp[0][0][0][1] = 1;
        // i: 현재 확인하는 z의 index
        for (int i = 0; i < max_len; i++) {
            // j: 지금까지의 최장 공통 연속 문자열의 길이가 r 이상?
            for (int j = 0; j <= 1; j++) {
                // k: 현재 index에서 최장 공통 연속 문자열의 길이
                for (int k = 0; k <= max_len; k++) {
                    // l: bound 상태
                    for (int l = 0; l <= 1; l++) {
                        if (l == 0) {
                            for (int d = 0; d <= 9; d++) {
                                if (d == z_v[i]) {
                                    dp[i + 1][max(j, (int)(k + 1 >= r))][k + 1][0] += dp[i][j][k][l];
                                } else {
                                    dp[i + 1][j][0][0] += dp[i][j][k][l];
                                }
                            }
                        } else {
                            for (int d = 0; d < max_v[i]; d++) {
                                if (d == z_v[i]) {
                                    dp[i + 1][max(j, (int)(k + 1 >= r))][k + 1][0] += dp[i][j][k][l];
                                } else {
                                    dp[i + 1][j][0][0] += dp[i][j][k][l];
                                }
                            }
                            int d = max_v[i];
                            if (d == z_v[i]) {
                                dp[i + 1][max(j, (int)(k + 1 >= r))][k + 1][1] += dp[i][j][k][l];
                            } else {
                                dp[i + 1][j][0][1] += dp[i][j][k][l];
                            }
                        }
                    }
                }
            }
        }

        ll ans = 0;
        for (int k = 0; k <= max_len; k++) {
            ans += dp[max_len][1][k][0];
            ans += dp[max_len][1][k][1];
        }

        cout << ans << "\n";
        for (int i = 0; i <= max_len; i++) {
            for (int j = 0; j <= 1; j++) {
                for (int k = 0; k <= max_len; k++) {
                    dp[i][j][k][0] = 0;
                    dp[i][j][k][1] = 0;
                }
            }
        }
    }

    return 0;
}