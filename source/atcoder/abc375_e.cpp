// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<int> teams(n), skills(n);
    int skill_sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> teams[i] >> skills[i];
        teams[i]--;
        skill_sum += skills[i];
    }

    if (skill_sum % 3 != 0) {
        cout << -1;
        return 0;
    }

    vector<vector<int>> dp(501, vector<int>(501, MOD1));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> dp_nxt(501, vector<int>(501, MOD1));
        for (int j = 500; j >= 0; j--) {
            for (int k = 500; k >= 0; k--) {
                if (dp[j][k] == -1) {
                    continue;
                }
                int nj = j + skills[i];
                int nk = k + skills[i];
                if (teams[i] == 0) {
                    if (nj <= 500)
                        dp_nxt[nj][k] = min(dp_nxt[nj][k], dp[j][k]);
                    if (nk <= 500)
                        dp_nxt[j][nk] = min(dp_nxt[j][nk], dp[j][k] + 1);
                    dp_nxt[j][k] = min(dp_nxt[j][k], dp[j][k] + 1);
                }
                else if (teams[i] == 1) {
                    if (nj <= 500)
                        dp_nxt[nj][k] = min(dp_nxt[nj][k], dp[j][k] + 1);
                    if (nk <= 500)
                        dp_nxt[j][nk] = min(dp_nxt[j][nk], dp[j][k]);
                    dp_nxt[j][k] = min(dp_nxt[j][k], dp[j][k] + 1);
                }
                else {
                    if (nj <= 500)
                        dp_nxt[nj][k] = min(dp_nxt[nj][k], dp[j][k] + 1);
                    if (nk <= 500)
                        dp_nxt[j][nk] = min(dp_nxt[j][nk], dp[j][k] + 1);
                    dp_nxt[j][k] = min(dp_nxt[j][k], dp[j][k]);
                }
            }
        }

        dp = dp_nxt;
    }

    cout << (dp[skill_sum / 3][skill_sum / 3] == MOD1 ? -1 : dp[skill_sum / 3][skill_sum / 3]);

    return 0;
}