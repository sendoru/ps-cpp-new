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
    cout << "Gnomes:\n";
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        if ((a >= b && b >= c) || (a <= b && b <= c))
            cout << "Ordered\n";
        else
            cout << "Unordered\n";
    }

    return 0;
}