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

        // case 1: x < n, it simply means x ^ n = x, so x = 0
        // case 2: x = n, trivial
        // case 3: x > n, x ^ n = x % n = x - n
        // as it's pretty obvious that x < 2n

        if (k == 1) {
            cout << n << endl;
        } else {
            k--;
            ll nn = n;
            int cur_bit = 0;
            vector<int> empty_bits;
            while (nn) {
                if (nn % 2 == 0) {
                    empty_bits.push_back(cur_bit);
                }
                nn /= 2;
                cur_bit++;
            }

            if (k >= (1 << empty_bits.size())) {
                cout << -1 << endl;
            } else {
                vector<int> bit_on(empty_bits.size(), 0);
                int i = 0;
                while (k) {
                    bit_on[i] = k % 2;
                    k /= 2;
                    i++;
                }
                ll ans = n;
                for (int i = 0; i < min(empty_bits.size(), bit_on.size()); i++) {
                    if (bit_on[i]) {
                        ans |= (1 << empty_bits[i]);
                    }
                }

                cout << ans << endl;
            }
        }
    }

    return 0;
}