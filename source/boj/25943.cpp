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
    ll a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (a > b) {
            b += x;
        } else {
            a += x;
        }
    }

    ll diff = abs(a - b);
    vector<ll> s = {100, 50, 20, 10, 5, 2, 1};
    ll ans = 0;
    for (ll x : s) {
        ans += diff / x;
        diff %= x;
    }

    cout << ans << "\n";

    return 0;
}