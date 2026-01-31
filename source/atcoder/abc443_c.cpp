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

    ll n, t;
    cin >> n >> t;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    ll last_open = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > last_open) {
            ans += a[i] - last_open;
            last_open = a[i] + 100;
        }
    }
    ans += max(0LL, t - last_open);
    cout << ans << '\n';

    return 0;
}