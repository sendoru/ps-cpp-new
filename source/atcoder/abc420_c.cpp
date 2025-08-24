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
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += min(a[i], b[i]);
    }

    while (q--) {
        char c;
        ll x, v;
        cin >> c >> x >> v;
        x--;
        ans -= min(a[x], b[x]);
        if (c == 'A') {
            a[x] = v;
        } else {
            b[x] = v;
        }
        ans += min(a[x], b[x]);
        cout << ans << "\n";
    }

    return 0;
}