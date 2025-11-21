#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
using namespace atcoder;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll segmax(ll a, ll b) {
    return a > b ? a : b;
}

ll e() {
    return 0LL;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;

    vector<ll> added(n + 10);
    vector<ll> diff(n + 10);
    for (int i = 0; i < q; i++) {
        ll idx, x;
        cin >> idx >> x;
        added[idx] += x;
        diff[idx - 1] = max(diff[idx - 1], added[idx - 1] - added[idx]);
        diff[idx] = max(diff[idx], added[idx] - added[idx + 1]);
    }

    ll ans = n * (n + 1) / 2;
    for (ll i = 1; i < n; i++) {
        ans += (n - i) * (diff[i]);
    }

    cout << ans << '\n';

    return 0;
}