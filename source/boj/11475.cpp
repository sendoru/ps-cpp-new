// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll get_min_time(vector<ll> &d, ll r) {
    vector<ll> dp(d.size(), 1e18);
    dp[0] = 0;

    deque<pll> dq;
    dq.push_back({0, 0});

    for (int i = 0; i < d.size(); i++) {
        while (!dq.empty() && dq.front().first < i - r) {
            dq.pop_front();
        }
        if (!dq.empty()) {
            dp[i] = dq.front().second + d[i] + i;
        }
        while (!dq.empty() && dq.back().second >= dp[i] - i) {
            dq.pop_back();
        }
        dq.push_back({i, dp[i] - i});
    }

    return dp.back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, t;
    cin >> n >> t;
    vector<ll> p(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
    }

    vector<ll> d(n);
    for (int i = 1; i < n - 1; i++) {
        cin >> d[i];
    }

    ll l = 1, r = n;
    ll ans = 1e18;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (get_min_time(d, mid) <= t) {
            ans = min(ans, mid);
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    if (ans == 1e18) {
        cout << -1 << '\n';
    } else {
        cout << *min_element(p.begin() + ans, p.end()) << '\n';
    }

    return 0;
}