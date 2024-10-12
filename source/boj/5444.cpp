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
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> cur(m, -1);
        int ans = 0;
        cur[0] = 0;
        for (int i = 0; i < n; i++) {
            vector<int> next(m, -1);
            for (int j = 0; j < m; j++) {
                if (cur[j] == -1) {
                    continue;
                }

                int next_mod = (j + a[i]) % m;
                next[next_mod] = max(next[next_mod], cur[j] + 1);
            }
            ans = max(ans, next[0]);
            for (int j = 0; j < m; j++) {
                next[j] = max(next[j], cur[j]);
            }
            cur = next;
        }

        cout << ans << '\n';
    }

    return 0;
}