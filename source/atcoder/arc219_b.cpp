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
        ll n;
        cin >> n;
        vector<ll> p(n);
        for (ll i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
        }

        // Q' is obtained by l = 0 and r = (position of 0 in Q) if 0 is not the first
        // Q' is obtained by l = 1 and r = (position of 1 in Q) if 0 is the first and 1 is NOT the second
        // Q' is obtained by l = 2 and r = (position of 2 in Q) if 0, 1 is the first two and 1 is NOT the third
        // and so on...
        ll ans = 0;
        for (ll i = 0; i < n; i++) {
            if (p[i] != i) {
                break;
            }
            ans += n - i - 1;
            if (i == n - 1) {
                ans++;
            }
        }

        cout << ans % MOD9 << "\n";
    }

    return 0;
}