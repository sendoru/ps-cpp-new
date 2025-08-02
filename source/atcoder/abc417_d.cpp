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
    vector<int> p(n), a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> a[i] >> b[i];
    }

    // dp[i][j] = 초기 기분이 j일 때, i번째 이후의 모든 선물을 받았을 때 최종 기분

    vector<vector<int>> dp(n + 1, vector<int>(2222, -1e9));
    function<int(int, int)> dfs = [&](int i, int j) {
        if (i == n) {
            return dp[i][j] = j;
        }
        if (dp[i][j] != -1e9) {
            return dp[i][j];
        }
        if (p[i] >= j) {
            return dp[i][j] = dfs(i + 1, j + a[i]);
        }
        else {
            return dp[i][j] = dfs(i + 1, max(j - b[i], 0));
        }
    };
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2222; j++) {
            dfs(i, j);
        }
    }

    vector<int> b_pf_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        b_pf_sum[i] = b_pf_sum[i - 1] + b[i - 1];
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        if (x < 2222) {
            cout << dp[0][x] << '\n';
        }
        else {
            auto it = upper_bound(b_pf_sum.begin(), b_pf_sum.end(), x - 2222);
            int offset = it - b_pf_sum.begin();
            if (offset == n + 1) {
                cout << x - b_pf_sum[n] << '\n';
            }
            else {
                cout << dp[offset][x - b_pf_sum[offset]] << '\n';
            }
        }
    }

    return 0;
}