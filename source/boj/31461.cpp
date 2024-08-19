#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve()
{
    ll n;
    cin >> n;
    vector<vector<ll>> s(2, vector<ll>(n));
    for (ll i = 0; i < n; i++) {
        cin >> s[0][i];
    }
    for (ll i = 0; i < n; i++) {
        cin >> s[1][i];
    }

    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    a--;
    b--;
    c--;
    d--;
    if (a == c) {
        ll ans = s[b][a] + s[d][c];
        ll added = 0;
        if (a != 0) {
            vector<vector<ll>> dp(a, vector<ll>(3, INT64_MIN));
            dp[a - 1][0] = s[0][a - 1];
            added = max(added, dp[a - 1][0]);
            dp[a - 1][1] = s[1][a - 1];
            added = max(added, dp[a - 1][1]);
            dp[a - 1][2] = s[0][a - 1] + s[1][a - 1];
            added = max(added, dp[a - 1][2]);
            for (int i = a - 2; i >= 0; i--) {
                dp[i][0] = s[0][i] + dp[i + 1][2];
                added = max(added, dp[i][0]);
                dp[i][1] = s[1][i] + dp[i + 1][2];
                added = max(added, dp[i][1]);
                dp[i][2] = s[0][i] + s[1][i] + dp[i + 1][2];
                added = max(added, dp[i][2]);
            }
        }
        if (a != n - 1) {
            vector<vector<ll>> dp(n - a - 1, vector<ll>(3, INT64_MIN));
            dp[0][0] = s[0][a + 1];
            added = max(added, dp[0][0]);
            dp[0][1] = s[1][a + 1];
            added = max(added, dp[0][1]);
            dp[0][2] = s[0][a + 1] + s[1][a + 1];
            added = max(added, dp[0][2]);
            for (int i = 1; i < n - a - 1; i++) {
                dp[i][0] = s[0][a + i + 1] + dp[i - 1][2];
                added = max(added, dp[i][0]);
                dp[i][1] = s[1][a + i + 1] + dp[i - 1][2];
                added = max(added, dp[i][1]);
                dp[i][2] = s[0][a + i + 1] + s[1][a + i + 1] + dp[i - 1][2];
                added = max(added, dp[i][2]);
            }
        }

        return ans + added;
    }
    if (b == 1) {
        b = 0;
        swap(s[0][a], s[1][a]);
    }
    if (d == 1) {
        d = 0;
        swap(s[0][c], s[1][c]);
    }
    if (a > c) {
        swap(a, c);
    }

    ll ans = s[b][a] + s[d][c];
    ll added = 0;
    if (a != 0) {
        vector<vector<ll>> dp(a, vector<ll>(3, INT64_MIN));
        dp[a - 1][0] = s[0][a - 1];
        added = max(added, dp[a - 1][0]);
        dp[a - 1][1] = s[1][a - 1];
        added = max(added, dp[a - 1][1]);
        dp[a - 1][2] = s[0][a - 1] + s[1][a - 1];
        added = max(added, dp[a - 1][2]);
        for (int i = a - 2; i >= 0; i--) {
            dp[i][0] = s[0][i] + dp[i + 1][2];
            added = max(added, dp[i][0]);
            dp[i][1] = s[1][i] + dp[i + 1][2];
            added = max(added, dp[i][1]);
            dp[i][2] = s[0][i] + s[1][i] + dp[i + 1][2];
            added = max(added, dp[i][2]);
        }
    }
    added = max(0ll, added + s[1][a]);
    ans += added;
    added = 0;
    if (c != n - 1) {
        vector<vector<ll>> dp(n - c - 1, vector<ll>(3, INT64_MIN));
        dp[0][0] = s[0][c + 1];
        added = max(added, dp[0][0]);
        dp[0][1] = s[1][c + 1];
        added = max(added, dp[0][1]);
        dp[0][2] = s[0][c + 1] + s[1][c + 1];
        added = max(added, dp[0][2]);
        for (int i = 1; i < n - c - 1; i++) {
            dp[i][0] = s[0][c + i + 1] + dp[i - 1][2];
            added = max(added, dp[i][0]);
            dp[i][1] = s[1][c + i + 1] + dp[i - 1][2];
            added = max(added, dp[i][1]);
            dp[i][2] = s[0][c + i + 1] + s[1][c + i + 1] + dp[i - 1][2];
            added = max(added, dp[i][2]);
        }
    }
    added = max(0ll, added + s[1][c]);
    ans += added;
    for (int i = a + 1; i < c; i++) {
        ans += max(s[0][i], max(s[1][i], s[0][i] + s[1][i]));
    }
    return ans;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }

    return 0;
}