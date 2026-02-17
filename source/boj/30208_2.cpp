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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, s;
    cin >> n >> s;
    vector<int> w(n + 1), t(n + 1), p(n + 1, -1);
    int w_sum = 0;
    vector<int> nxt(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w_sum += w[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        nxt[p[i]] = i;
    }

    if (accumulate(w.begin(), w.end(), 0) < s) {
        cout << -1;
        return 0;
    }

    vector<int> dp(w_sum + 1, 1e6);
    dp[0] = 0;
    vector<bool> visited(n + 1);
    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            continue;
        }
        visited[i] = true;
        int chain_w_sum = 0;
        int cur = i;
        while (cur != -1) {
            visited[cur] = true;
            chain_w_sum += w[cur];
            cur = nxt[cur];
        }
        vector<array<int, 2>> cur_combs;
        cur = i;
        int cur_w_sum = 0, cur_t_sum = 0;
        while (cur != -1) {
            cur_w_sum += w[cur];
            cur_t_sum += t[cur];
            cur_combs.push_back({cur_w_sum, cur_t_sum});
            cur = nxt[cur];
        }

        for (int j = w_sum - chain_w_sum; j >= 0; j--) {
            for (auto [cw, ct] : cur_combs) {
                dp[j + cw] = min(dp[j + cw], dp[j] + ct);
            }
        }
    }

    int ans = 1e6;
    for (int i = s; i <= w_sum; i++) {
        ans = min(ans, dp[i]);
    }
    cout << ans;

    return 0;
}