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

    ll n, m, k;
    cin >> n >> m >> k;
    ll x, y;
    cin >> x >> y;
    vector<ll> a(n), b(m);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (ll i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll remain = x + y * k;
    vector<ll> x_pf_sum(n);
    x_pf_sum[0] = a[0];
    for (int i = 1; i < n; i++) {
        x_pf_sum[i] = x_pf_sum[i - 1] + a[i];
    }
    ll ans = upper_bound(x_pf_sum.begin(), x_pf_sum.end(), remain) - x_pf_sum.begin();
    for (int i = 0; i < m; i++) {
        ll need = (b[i] + k - 1) / k;
        if (need > y) {
            break;
        }
        remain -= b[i];
        y -= need;
        ans = max(ans, i + 1 + (ll)(upper_bound(x_pf_sum.begin(), x_pf_sum.end(), remain) - x_pf_sum.begin()));
    }

    cout << ans;
    return 0;
}