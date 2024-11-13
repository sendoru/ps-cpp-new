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
        ll l1, h1, l2, h2;
        cin >> l1 >> h1 >> l2 >> h2;
        ll s1 = l1 * h1, s2 = l2 * h2;
        if (s1 > s2) {
            cout << "TelecomParisTech\n";
        } else if (s1 == s2) {
            cout << "Tie\n";
        } else {
            cout << "Eurecom\n";
        }
    }

    return 0;
}