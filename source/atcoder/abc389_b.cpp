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

    ll x;
    cin >> x;
    ll cur = 1;
    for (ll i = 1; cur <= x; i++) {
        cur *= i;
        if (cur == x) {
            cout << i << endl;
            return 0;
        }
        if (cur > x) {
            cout << -1 << endl;
            return 0;
        }
    }
}