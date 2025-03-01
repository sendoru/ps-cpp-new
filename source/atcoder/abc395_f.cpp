// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, x;
    cin >> n >> x;
    vector<ll> u(n), d(n), sum(n);
    ll all_sum = 0;
    for (ll i = 0; i < n; i++) {
        cin >> u[i] >> d[i];
        sum[i] = u[i] + d[i];
        all_sum += sum[i];
    }

    ll lo = 0, hi = *min_element(sum.begin(), sum.end());
    ll ans = 0;

    while (lo <= hi) {
        // mid : target sum
        ll mid = (lo + hi) / 2;
        vector<ll> u_min(n), u_max(n);
        for (int i = 0; i < n; i++) {
            u_min[i] = max(0ll, mid - d[i]);
            u_max[i] = min(mid, u[i]);
        }
        // within the range u_min <= v <= u_max,
        // is it possible to make v s.t. abs(v[i] - v[i-1]) <= x?
        bool ok = true;
        for (int i = 1; i < n; i++) {
            ll bottom = max(0ll, u_min[i - 1] - x);
            ll top = u_max[i - 1] + x;
            u_min[i] = max(u_min[i], bottom);
            u_max[i] = min(u_max[i], top);
            if (u_min[i] > u_max[i]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ans = max(ans, mid);
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << all_sum - ans * n << '\n';

    return 0;
}