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

    string s;
    cin >> s;
    int n = s.size();

    int ans = 0;

    // odd length quasipalindromes
    for (int mid = 0; mid < n; mid++) {
        int need = 0;
        for (int rad = 0; rad < n; rad++) {
            if (mid - rad < 0 || mid + rad >= n) {
                break;
            }
            if (s[mid - rad] != s[mid + rad]) {
                need++;
            }
            if (need > 1) {
                break;
            }
            ans++;
        }
    }

    // even length
    for (int mid = 0; mid < n - 1; mid++) {
        int need = 0;
        for (int rad = 0; rad < n; rad++) {
            if (mid - rad < 0 || mid + 1 + rad >= n) {
                break;
            }
            if (s[mid - rad] != s[mid + 1 + rad]) {
                need++;
            }
            if (need > 1) {
                break;
            }
            ans++;
        }
    }

    cout << ans;

    return 0;
}