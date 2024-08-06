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

    int ff, fs, sf, ss;
    cin >> ff >> fs >> sf >> ss;

    if (ff == 0 && fs == 0) {
        cout << ss + (sf > 0 ? 1 : 0);
    } else {
        int ans = ff + 2 * min(fs, sf);
        if (fs != 0 && sf != 0) {
            ans = max(ans, ff + ss + 2 * min(fs, sf));
        }
        if (fs != 0) {
            ans = max(ans, ff + ss + 2 * min(fs, sf + 1) - 1);
        }
        cout << ans;
    }

    return 0;
}