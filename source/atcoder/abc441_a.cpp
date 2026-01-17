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

    int p, q, x, y;
    cin >> p >> q >> x >> y;
    if (x >= p && x <= p + 99 && y >= q && y <= q + 99) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}