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

    ll n, a, b;
    cin >> n >> a >> b;
    if (__gcd(a, b) != 1) {
        cout << "No\n"
             << endl;
        return 0;
    }

    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        ll l = a + 2 * i * b;
        ll r = a + (2 * i + 1) * b;
        assert(__gcd(l, r) == 1);
        cout << l << " " << r << "\n";
    }

    return 0;
}