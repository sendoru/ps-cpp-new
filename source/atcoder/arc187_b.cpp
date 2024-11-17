// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    if (e == 0) {
        return 1;
    }
    if (e % 2 == 0) {
        ll t = modpow(b, e / 2, m);
        return t * t % m;
    }
    return b * modpow(b, e - 1, m) % m;
}

ll solve(vector<ll> &b, int m) {
    int n = b.size();

    for (int i = 0; i < n; i++) {
        if (b[i] == -1) {
            b[i] = INT64_MAX;
        }
    }

    vector<ll> prefix_min(n);
    vector<ll> undef_cnt(n);
    prefix_min[0] = b[0];
    undef_cnt[0] = b[0] == INT64_MAX ? 1 : 0;
    for (int i = 1; i < n; i++) {
        prefix_min[i] = min(prefix_min[i - 1], b[i]);
        undef_cnt[i] = undef_cnt[i - 1] + (b[i] == INT64_MAX ? 1 : 0);
    }

    vector<ll> dp(n);
    dp[0] = b[0] == INT64_MAX ? m : 1;
    for (int i = 1; i < n; i++) {
        // case 1: b[i] != -1 (fixed)
        if (b[i] != INT64_MAX) {
            if (b[i] >= prefix_min[i - 1]) {
                dp[i] = dp[i - 1];
            } else {
                // undef_cnt[i - 1]개 -1이 모두 b[i]보다 큰 경우의 수
                // = (m - b[i]) ** (undef_cnt[i - 1])
                // 이때는 연결요소 갯수 1 증가
                ll case_cnt = modpow(m - b[i], undef_cnt[i - 1], MOD9);
                dp[i] = (dp[i - 1] + case_cnt) % MOD9;
            }
        } else {
            for (int j = 1; j <= m; j++) {
                if (j >= prefix_min[i - 1]) {
                    dp[i] += modpow(m, undef_cnt[i - 1], MOD9);
                    dp[i] %= MOD9;
                } else {
                    ll case_cnt = modpow(m - j, undef_cnt[i - 1], MOD9);
                    dp[i] += dp[i - 1] + case_cnt;
                    dp[i] %= MOD9;
                }
            }
        }
    }

    return dp[n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    cout << solve(b, m) << '\n';

    return 0;
}