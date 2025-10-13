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
        ll n, k;
        cin >> n >> k;
        ll lo = 2, hi = 2 * k + 2;
        ll a_0 = 1e18;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            vector<ll> a;
            a.push_back(mid);
            while (a.back() - a[0] < k && a.size() < n) {
                a.push_back(a.back() * 2 - 1);
            }
            if (a.back() - a[0] >= k) {
                a_0 = min(a_0, mid);
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        vector<ll> ans(n);
        ans[0] = a_0;
        for (int i = 1; i < n; i++) {
            ans[i] = min(ans[i - 1] * 2 - 1, ans[0] + k);
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}