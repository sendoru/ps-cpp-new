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

    ll a, b;
    while (1) {
        cin >> a >> b;
        if (a == 0 && b == 0) {
            break;
        }
        map<ll, ll> ma, mb;
        ll len_a = 1, len_b = 1;
        ll cur_a = a, cur_b = b;
        ll prev_a, prev_b;

        while (ma.find(cur_a) == ma.end()) {
            ma[cur_a] = len_a;
            len_a++;
            prev_a = cur_a;
            cur_a = 0;
            while (prev_a) {
                cur_a += (prev_a % 10) * (prev_a % 10);
                prev_a /= 10;
            }
        }

        while (mb.find(cur_b) == mb.end()) {
            mb[cur_b] = len_b;
            len_b++;
            prev_b = cur_b;
            cur_b = 0;
            while (prev_b) {
                cur_b += (prev_b % 10) * (prev_b % 10);
                prev_b /= 10;
            }
        }

        ll ans = 1e12;
        for (auto it = ma.begin(); it != ma.end(); it++) {
            if (mb.find(it->first) != mb.end()) {
                ans = min(ans, it->second + mb[it->first]);
            }
        }

        if (ans == 1e12) {
            ans = 0;
        }
        cout << a << ' ' << b << ' ' << ans << '\n';
        cout.flush();
    }

    return 0;
}