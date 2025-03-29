// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            cin >> a[i];
            a[i]--;
        }
        vector<vector<int>> pos(n);
        for (int i = 0; i < 2 * n; i++) {
            pos[a[i]].push_back(i);
        }

        ll ans = 0;
        for (int i = 0; i < n; i++) {
            int x = pos[i][0], y = pos[i][1];
            if (abs(x - y) == 1) {
                continue;
            }
            for (int dx = -1; dx <= 1; dx += 2) {
                int nx = x + dx;
                if (nx < 0 || nx >= 2 * n) {
                    continue;
                }
                for (int dy = -1; dy <= 1; dy += 2) {
                    int ny = y + dy;
                    if (ny < 0 || ny >= 2 * n) {
                        continue;
                    }
                    if (abs(nx - ny) <= 1) {
                        continue;
                    }
                    if (a[nx] == a[ny]) {
                        ans++;
                    }
                }
            }
        }

        cout << ans / 2 << "\n";
    }

    return 0;
}