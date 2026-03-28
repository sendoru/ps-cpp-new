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
    vector<array<ll, 2>> ab1, ab2;
    ll cur = 0;
    for (int i = 1; i <= n; i++) {
        ll a, b;
        cin >> a >> b;
        if (b >= a) {
            ab1.push_back({a, b});
        } else {
            ab2.push_back({a, b});
        }
    }

    sort(ab1.begin(), ab1.end());
    sort(ab2.begin(), ab2.end(), [](auto &x, auto &y) {
        if (x[1] == y[1]) {
            return x[0] < y[0];
        }
        return x[1] > y[1];
    });

    for (auto [a, b] : ab1) {
        if (cur >= a) {
            cur += b - a;
        } else {
            cout << 0;
            return 0;
        }
    }

    for (auto [a, b] : ab2) {
        if (cur >= a) {
            cur += b - a;
        } else {
            cout << 0;
            return 0;
        }
    }

    cout << 1;
    return 0;
}