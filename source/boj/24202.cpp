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

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    ll ans = 0;
    ll bound = accumulate(a.begin(), a.end(), 0ll) / 2 + 1;

    for (int i = 0; i < n; i++) {
        vector<ll> a_sub(a.begin() + i + 1, a.end());
        vector<ll> left, right;
        int m = a_sub.size();

        // mitm subset sum
        int half = m / 2;
        for (int mask = 0; mask < (1 << half); mask++) {
            ll sum = 0;
            for (int j = 0; j < half; j++) {
                if (mask & (1 << j)) {
                    sum += a_sub[j];
                }
            }
            left.push_back(sum);
        }
        for (int mask = 0; mask < (1 << (m - half)); mask++) {
            ll sum = 0;
            for (int j = 0; j < m - half; j++) {
                if (mask & (1 << j)) {
                    sum += a_sub[half + j];
                }
            }
            right.push_back(sum);
        }
        sort(right.begin(), right.end());

        // 1) left[j] + right[k] + a[i] >= bound
        // 2) left[j] + right[k] < bound
        for (ll x : left) {
            ll lower = bound - a[i] - x;
            ll upper = bound - x;
            auto it_low = lower_bound(right.begin(), right.end(), lower);
            auto it_up = lower_bound(right.begin(), right.end(), upper);
            ans += it_up - it_low;
        }
    }

    cout << ans << '\n';

    return 0;
}