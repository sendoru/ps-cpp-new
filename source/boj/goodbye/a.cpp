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
    vector<string> ans1(2 * n), ans2(2 * n);
    for (int i = 0, j = 2 * n - 1; i < 2 * n; i++, j--) {
        ans1[i] = string(2 * n + 1, ' ');
        ans1[i][j] = '*';
    }
    for (int i = 0, j = n - 1; i < n; i++, j--) {
        ans2[i] = string(2 * n + 1, ' ');
        ans2[i][j] = '*';
        ans2[i][2 * n - j] = '*';
    }
    for (int i = n; i < 2 * n; i++) {
        ans2[i] = ans2[2 * n - 1 - i];
    }

    for (int i = 0; i < 2 * n; i++) {
        cout << ans1[i] << ans2[i] << '\n';
    }

    return 0;
}

/*
     *   * *
    *   *   *
   *   *     *
  *    *     *
 *      *   *
*        * *

     *   * *
    *   *   *
   *   *     *
  *    *     *
 *      *   *
*        * *
*/