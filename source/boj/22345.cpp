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

    int n, q;
    cin >> n >> q;
    vector<array<ll, 2>> ax(n);
    for (int i = 0; i < n; i++) {
        cin >> ax[i][0] >> ax[i][1];
    }

    sort(ax.begin(), ax.end(), [](const array<ll, 2> &a, const array<ll, 2> &b) {
        return a[1] < b[1];
    });

    vector<ll> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = ax[i][1];
    }

    vector<ll> pf_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pf_sum[i + 1] = pf_sum[i] + ax[i][0];
    }
    vector<ll> pf_sum_2(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pf_sum_2[i + 1] = pf_sum_2[i] + ax[i][0] * ax[i][1];
    }

    while (q--) {
        int q;
        cin >> q;
        int idx = lower_bound(x.begin(), x.end(), q) - x.begin();
        ll ans = 0;
        ans += pf_sum[idx] * q - pf_sum_2[idx];
        ans += (pf_sum_2[n] - pf_sum_2[idx]) - (pf_sum[n] - pf_sum[idx]) * q;
        cout << ans << '\n';
    }

    return 0;
}