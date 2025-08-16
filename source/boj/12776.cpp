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

    ll n;
    cin >> n;
    vector<pll> plus, minus;
    for (ll i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        if (b >= a) {
            plus.emplace_back(a, b);
        } else {
            minus.emplace_back(a, b);
        }
    }

    sort(plus.begin(), plus.end(), [](const pll &x, const pll &y) {
        if (x.first == y.first) {
            return x.second > y.second;
        }
        return x.first < y.first;
    });

    ll surplus = 0, ans = 0;
    for (const auto &[a, b] : plus) {
        if (a > surplus) {
            ans += a - surplus;
            surplus = b;
        } else {
            surplus -= a;
            surplus += b;
        }
    }

    sort(minus.begin(), minus.end(), [](const pll &x, const pll &y) {
        return x.second > y.second;
    });

    for (const auto &[a, b] : minus) {
        if (a > surplus) {
            ans += a - surplus;
            surplus = b;
        } else {
            surplus -= a;
            surplus += b;
        }
    }

    cout << ans << '\n';

    return 0;
}