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
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {

        int n;
        cin >> n;
        vector<int> row1(2 * n), row2(n), col1(2 * n), col2(n);
        int ans = 2 * n;

        for (int i = 0, x = 1; x <= 2 * n; i++, x += 2) {
            cout << "? " << x << ' ' << '1' << ' ' << x + 1 << ' ' << 2 * n << endl;
            cin >> row2[i];
            if (row2[i] == 0) {
                continue;
            }
            if (row2[i] == 1) {
                ans--;
                continue;
            }
            cout << "? " << x << ' ' << '1' << ' ' << x << ' ' << 2 * n << endl;
            cin >> row1[i * 2];
            if (row1[i * 2] == 0 || row1[i * 2] == row2[i]) {
                ans--;
            } else {
                ans -= 2;
            }
        }

        for (int i = 0, x = 1; x <= 2 * n; i++, x += 2) {
            cout << "? " << '1' << ' ' << x << ' ' << 2 * n << ' ' << x + 1 << endl;
            cin >> row2[i];
            if (row2[i] == 0) {
                continue;
            }
            if (row2[i] == 1) {
                ans--;
                continue;
            }
            cout << "? " << '1' << ' ' << x << ' ' << 2 * n << ' ' << x << endl;
            cin >> row1[i * 2];
            if (row1[i * 2] == 0 || row1[i * 2] == row2[i]) {
                ans--;
            } else {
                ans -= 2;
            }
        }

        cout << "! " << ans << endl;
    }

    return 0;
}