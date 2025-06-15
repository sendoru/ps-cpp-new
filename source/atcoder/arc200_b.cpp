// #include "atcoder/all"
#define DEBUG
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pll solve(int a1, int a2, int a3) {
    bool swapped = false;
    if (a1 > a2) {
        swap(a1, a2);
        swapped = true;
    }
    if (a3 < a1 || a3 < a2) {
        return {-1, -1}; // No solution
    }
    if (a3 > a1 + a2) {
        return {-1, -1}; // No solution
    }
    ll x1, x2;
    if (a1 == a2 && a2 == a3) {
        // any a1 digit works
        x1 = powl(10, a1 - 1);
        x2 = x1;
    } else if (a1 < a2 && a2 == a3) {
        x1 = powl(10, a1 - 1);
        x2 = powl(10, a2 - 1);
    } else {
        if (a3 == a1 + a2) {
            x1 = 8 * (ll)powl(10, a1 - 1);
            x2 = 8 * (ll)powl(10, a2 - 1) + 1;
        } else {
            ll p = a1 + a2 - a3 - 1;
            x1 = (ll)powl(10, a1 - 1);
            x2 = (ll)powl(10, a2 - 1) + (ll)powl(10, p);
        }
    }
    if (swapped) {
        swap(x1, x2);
        swap(a1, a2);
    }
    ll lcm = (__int128_t(x1) * x2) / __gcd(x1, x2);
    assert(to_string(x1).length() == a1 && to_string(x2).length() == a2 && to_string(lcm).length() == a3);
    return {x1, x2};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    for (int i = 1; i <= 17; i++) {
        for (int j = 1; j <= 17; j++) {
            for (int k = 1; k <= 17; k++) {
                pll ans = solve(i, j, k);
            }
        }
    }
#endif

    int t;
    cin >> t;
    while (t--) {
        int a1, a2, a3;
        cin >> a1 >> a2 >> a3;
        pll ans = solve(a1, a2, a3);
        if (ans.first == -1 && ans.second == -1) {
            cout << "No\n";
        } else {
            cout << "Yes\n"
                 << ans.first << " " << ans.second << "\n";
        }
    }

    return 0;
}