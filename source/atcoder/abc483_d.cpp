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

    ll n;
    cin >> n;
    vector<ll> a(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<pll> range(n + 2), range_rev(n + 2);
    vector<ll> culm(n + 2);
    ll max_val = 0, min_val = 0, cur_val = 0;
    for (int i = 1; i <= n; i++) {
        cur_val += a[i];
        max_val = max(max_val, cur_val);
        min_val = min(min_val, cur_val);
        range[i] = {min_val, max_val};
        culm[i] = cur_val;
    }

    ll ans = max_val - min_val + 1;

    cur_val = 0;
    max_val = 0;
    min_val = 0;
    for (int i = n; i >= 1; i--) {
        range_rev[i] = range_rev[i + 1];
        range_rev[i].first += a[i];
        range_rev[i].second += a[i];
        range_rev[i].first = min(range_rev[i].first, 0LL);
        range_rev[i].second = max(range_rev[i].second, 0LL);
        cur_val += a[i];
    }

    for (int i = 1; i <= n; i++) {
        ll min_val_1 = range[i - 1].first;
        ll max_val_1 = range[i - 1].second;
        ll min_val_2 = range_rev[i + 1].first + culm[i - 1] - a[i];
        ll max_val_2 = range_rev[i + 1].second + culm[i - 1] - a[i];
        ll cur_min_val = min(min_val_1, min_val_2);
        ll cur_max_val = max(max_val_1, max_val_2);
        ans = max(ans, cur_max_val - cur_min_val + 1);
    }

    cout << ans;

    return 0;
}