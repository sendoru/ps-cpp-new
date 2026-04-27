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
        vector<array<ll, 4>> info(n);
        for (int i = 0; i < n; i++) {
            cin >> info[i][0] >> info[i][1] >> info[i][2] >> info[i][3];
        }
        sort(info.begin(), info.end(), [](const auto &a, const auto &b) {
            return a[3] < b[3];
        });
        for (int i = n - 2; i >= 0; i--) {
            info[i][3] = min(info[i][3], info[i + 1][3] - 1);
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                info[i][j] = max(info[i][j], info[i - 1][j]);
            }
        }
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (info[i][0] + info[i][1] + info[i][2] > info[i][3] - (i + 1)) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}