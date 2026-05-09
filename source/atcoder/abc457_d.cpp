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

    ll n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll lo = *min_element(a.begin() + 1, a.end());
    ll hi = 2e18;
    ll ans = lo;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        ll need = 0;
        for (ll i = 1; i <= n; i++) {
            ll diff = max(0LL, mid - a[i]);
            need += (diff + i - 1) / i;
            // prevent overflow
            if (need > k) {
                break;
            }
        }
        if (need <= k) {
            ans = max(ans, mid);
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << ans;

    return 0;
}