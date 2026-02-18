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
        int n;
        cin >> n;
        vector<array<ll, 2>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i][0] >> a[i][1];
        }
        sort(a.begin(), a.end());
        ll ans = 1;
        ll min_second = a[0][1];
        for (int i = 1; i < n; i++) {
            if (a[i][1] < min_second) {
                ans++;
                min_second = a[i][1];
            }
        }
        cout << ans << "\n";
    }

    return 0;
}