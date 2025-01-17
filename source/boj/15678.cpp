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

    ll n, d;
    cin >> n >> d;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> dp(n, LLONG_MIN);
    dp[0] = a[0];

    deque<pll> dq;
    dq.push_back({0, a[0]});

    for (int i = 1; i < n; i++) {
        while (!dq.empty() && dq.front().first < i - d) {
            dq.pop_front();
        }
        dp[i] = max(0ll, dq.front().second) + a[i];
        while (!dq.empty() && dq.back().second <= dp[i]) {
            dq.pop_back();
        }
        dq.push_back({i, dp[i]});
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}