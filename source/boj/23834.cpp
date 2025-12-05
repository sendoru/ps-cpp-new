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

    ll n, m;
    cin >> n >> m;
    // index 0 and n + 1 for terminal condition
    vector<ll> a(n + 2), b(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<ll> dp(n + 2, 0);
    deque<pll> deq; // {val, idx}
    ll cur_a_sum = a[0];
    dp[0] = -a[0];
    deq.push_back({dp[0] - cur_a_sum, 0});
    for (int i = 1; i <= n + 1; i++) {
        // pop front (out of range)
        while (!deq.empty() && deq.front().second < i - m) {
            deq.pop_front();
        }
        dp[i] = deq.front().first + cur_a_sum - a[i];
        cur_a_sum += a[i];
        // remove smaller values
        while(!deq.empty() && deq.back().first <= dp[i] - cur_a_sum) {
            deq.pop_back();
        }
        deq.push_back({dp[i] - cur_a_sum, i});
    }

    cur_a_sum = 0;
    ll ans = 0;
    for (int i = 1; i <= min(n, m); i++) {
        cur_a_sum += a[i];
    }
    for (int i = 0; i <= n + 1; i++) {
        if (i + m < b.size()) {
            ans = max(ans, dp[i] + cur_a_sum + b[i + m]);
        }
        else {
            ans = max(ans, dp[i] + cur_a_sum);
        }
        if (i != n + 1) {
            cur_a_sum -= a[i + 1];
            if (i + m + 1 <= n) {
                cur_a_sum += a[i + m + 1];
            }
        }
    }

    cout << ans << "\n";

    return 0;
}