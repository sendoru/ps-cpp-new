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

    int n, p;
    cin >> n >> p;
    vector<array<ll, 2>> ab;
    ll ans1 = 0, ans2 = 1;
    for (int i = 1; i <= n; i++) {
        ll a, b;
        cin >> a >> b;
        assert(b > 0);
        if (i == p) {
            ans1 = a;
        } else if (a >= b) {
            ab.push_back({a, b});
        }
    }

    sort(ab.begin(), ab.end(), [](auto &x, auto &y) {
        return x[1] < y[1];
    });

    for (auto [a, b] : ab) {
        if (ans1 >= b) {
            ans1 += a - b;
            ans2++;
        } else {
            break;
        }
    }

    cout << ans1 << '\n'
         << ans2;

    return 0;
}