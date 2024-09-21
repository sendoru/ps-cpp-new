// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll l1_dist(pll a, pll b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pll> dots(n);
    for (int i = 0; i < n; i++) {
        cin >> dots[i].first >> dots[i].second;
    }

    vector<ll> cum_dist(n);
    for (int i = 1; i < n; i++) {
        cum_dist[i] = cum_dist[i - 1] + l1_dist(dots[i - 1], dots[i]);
    }

    ll ans = LLONG_MAX;
    for (int i = 1; i < n - 1; i++) {
        // skip i-th dot
        ll dist = cum_dist[n - 1];
        dist -= l1_dist(dots[i - 1], dots[i]) + l1_dist(dots[i], dots[i + 1]);
        dist += l1_dist(dots[i - 1], dots[i + 1]);
        ans = min(ans, dist);
    }

    cout << ans << '\n';

    return 0;
}