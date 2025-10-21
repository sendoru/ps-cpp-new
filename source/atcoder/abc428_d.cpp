// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// get the number of perfect squares leq x
ll count_smaller_squares(ll x) {
    ll root = (ll)sqrtl(x);
    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll c, d;
        cin >> c >> d;
        ll ans = 0;
        for (ll i = to_string(c).length(); i <= 11; i++) {
            ll min_subfix = pow(10, i - 1);
            min_subfix = max(min_subfix, c);
            ll max_subfix = pow(10, i) - 1;
            ll diff = max_subfix - c;
            bool done = false;
            if (diff >= d) {
                done = true;
                max_subfix = c + d;
            }
            ll min_num = stoll(to_string(c) + to_string(min_subfix));
            ;
            ll max_num = stoll(to_string(c) + to_string(max_subfix));
            ans += count_smaller_squares(max_num) - count_smaller_squares(min_num - 1);
            if (done) {
                break;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}