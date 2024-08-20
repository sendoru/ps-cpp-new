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

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int ans = 0;

        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        sort(v.begin(), v.end());

        int cur = 1;
        ans += cur;
        for (int i = 1; i < n; i++) {
            if (v[i] > v[i - 1]) {
                cur++;
            }
            ans += cur;
        }
        cout << "Case #" << t << ": ";
        cout << ans << "\n";
    }

    return 0;
}