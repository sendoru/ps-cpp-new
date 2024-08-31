#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// return v[start % n] + v[(start + 1) % n] + ... + v[(start + cnt - 1) % n]
// where prefix_sum[i] = v[0] + v[1] + ... + v[i]
ll get_circular_sum(vector<ll> &prefix_sum, int start, int cnt)
{
    if (start + cnt - 1 < prefix_sum.size()) {
        return prefix_sum[start + cnt - 1] - (start == 0 ? 0 : prefix_sum[start - 1]);
    }
    return prefix_sum.back() - (start == 0 ? 0 : prefix_sum[start - 1]) + prefix_sum[start + cnt - 1 - prefix_sum.size()];
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> v(n);

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
    }

    vector<ll> prefix_sum(n);
    prefix_sum[0] = v[0];
    for (int i = 1; i < n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + v[i];
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != 0 && j == n) {
                continue;
            }
            ll cur = get_circular_sum(prefix_sum, i, j);
            if (cur < 0) {
                ans += ceil((ld)abs(cur) / sum);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}