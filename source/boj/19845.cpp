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

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;

        if (a[y] - x <= 0) {
            cout << 0 << '\n';
            continue;
        }

        // same row
        ll ans = a[y] - x;

        // same col
        auto iter = upper_bound(a.begin(), a.end(), x + 1, greater<ll>());
        ans += max(0ll, iter - a.begin() - 1ll - y);
        cout << ans << '\n';
    }

    return 0;
}