// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<ll> left, right;
    for (int i = 0; i < n / 2; i++) {
        left.push_back(v[i]);
    }
    for (int i = n / 2; i < n; i++) {
        right.push_back(v[i]);
    }

    vector<ll> left_sum, right_sum;
    for (int i = 0; i < (1 << left.size()); i++) {
        ll sum = 0;
        for (int j = 0; j < left.size(); j++) {
            if (i & (1 << j)) {
                sum += left[j];
            }
        }
        left_sum.push_back(sum);
    }

    for (int i = 0; i < (1 << right.size()); i++) {
        ll sum = 0;
        for (int j = 0; j < right.size(); j++) {
            if (i & (1 << j)) {
                sum += right[j];
            }
        }
        right_sum.push_back(sum);
    }

    sort(right_sum.begin(), right_sum.end());

    ll ans = 0;
    for (int i = 0; i < left_sum.size(); i++) {
        ll target = m - left_sum[i];
        auto it = upper_bound(right_sum.begin(), right_sum.end(), target);
        ans += it - right_sum.begin();
    }

    cout << ans << '\n';

    return 0;
}