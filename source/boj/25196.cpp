// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool is_ok(ll t, ll s, ll e, ll n)
{
    n %= t;
    return s <= n && n <= e;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll at, as, ae;
    ll bt, bs, be;
    ll ct, cs, ce;

    cin >> at >> as >> ae;
    cin >> bt >> bs >> be;
    cin >> ct >> cs >> ce;

    ll ans = INT64_MAX;

    for (ll i = as; i <= at * bt * ct; i += at) {
        if (is_ok(bt, bs, be, i) && is_ok(ct, cs, ce, i)) {
            ans = min(ans, i);
        }
    }

    for (ll i = bs; i <= bt * ct * at; i += bt) {
        if (is_ok(at, as, ae, i) && is_ok(ct, cs, ce, i)) {
            ans = min(ans, i);
        }
    }

    for (ll i = cs; i <= ct * at * bt; i += ct) {
        if (is_ok(at, as, ae, i) && is_ok(bt, bs, be, i)) {
            ans = min(ans, i);
        }
    }

    if (ans == INT64_MAX) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }

    return 0;
}