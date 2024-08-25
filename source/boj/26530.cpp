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

    int t;
    cin >> t;
    while (t--) {
        int cnt;
        cin >> cnt;
        double ans = 0;
        for (int i = 0; i < cnt; i++) {
            string s;
            int n;
            double x;
            cin >> s >> n >> x;
            ans += n * x;
        }
        cout << fixed << setprecision(2) << '$' << ans << '\n';
    }

    return 0;
}