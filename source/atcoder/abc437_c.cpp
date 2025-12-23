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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pll> wp(n);
        for (int i = 0; i < n; i++) {
            cin >> wp[i].first >> wp[i].second;
        }

        sort(wp.begin(), wp.end(), [](const pll &a, const pll &b) {
            ll lhs = a.first + a.second;
            ll rhs = b.first + b.second;
            if (lhs != rhs) {
                return lhs < rhs;
            }
            return a.first > b.first;
        });
        ll p_sum = 0;
        for (int i = 0; i < n; i++) {
            p_sum += wp[i].second;
        }
        ll res = 0;
        for (int i = 0; i < n; i++) {
            p_sum -= wp[i].second;
            p_sum -= wp[i].first;
            if (p_sum >= 0) {
                res = max(res, i + 1ll);
            }
        }
        cout << res << "\n";
    }

    return 0;
}