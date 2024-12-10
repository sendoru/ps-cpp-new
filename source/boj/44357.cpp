// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll MOD = 1e9;

vector<vector<ll>> dp(1500, vector<ll>(1500, -1));

ll solve(ll n, ll h)
{
    if (h < 0 || n < 0) {
        return 0;
    }

    if (dp[n][h] != -1) {
        return dp[n][h];
    }

    if (n == 0) {
        return h == 0 ? 1 : 0;
    }
    if (n == 1) {
        return h == 1 ? 1 : 0;
    }
    if (n == 2) {
        return h == 2 ? 2 : 0;
    }

    ll &ret = dp[n][h] = 0;

    for (int l_n = 1; l_n < n; l_n++) {
        int r_n = n - 1 - l_n;
        ret = ret + solve(l_n, h - 1) * solve(r_n, h - 1) % MOD;
        ret = ret + solve(l_n, h - 2) * solve(r_n, h - 1) % MOD;
        ret = ret + solve(l_n, h - 1) * solve(r_n, h - 2) % MOD;
        ret %= MOD;
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n;
        cin >> n;
        if (!cin.good()) {
            break;
        }
        ll h = ceil(log2(n + 1));
        ll ans = 0;

        for (int i = max(0ll, h - 5); i <= min(n, h + 5); i++) {
            ans += solve(n, i);
            ans %= MOD;
        }
        string ans_str = to_string(ans);
        while (ans_str.size() < 9) {
            ans_str = '0' + ans_str;
        }
        cout << ans_str << '\n';
    }

    return 0;
}