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
    vector<ll> a(n);
    map<ll, vector<ll>> inv_a;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        inv_a[a[i]].push_back(i);
    }

    ll ans = 0;
    for (int j = 0; j < n; j++) {
        ll val = a[j];
        if (val % 5) {
            continue;
        }
        ll t1 = val / 5 * 3, t2 = val / 5 * 7;
        if (!inv_a.count(t1) || !inv_a.count(t2)) {
            continue;
        }
        auto& v1 = inv_a[t1];
        auto& v2 = inv_a[t2];
        ll c1, c2;
        // j being leftest
        c1 = v1.end() - upper_bound(v1.begin(), v1.end(), j);
        c2 = v2.end() - upper_bound(v2.begin(), v2.end(), j);
        ans += c1 * c2;
        // j being rightest
        c1 = lower_bound(v1.begin(), v1.end(), j) - v1.begin();
        c2 = lower_bound(v2.begin(), v2.end(), j) - v2.begin();
        ans += c1 * c2;
    }

    cout << ans;

    return 0;
}