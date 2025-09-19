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
    ld b;
    cin >> n >> b;
    vector<ld> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    ld lo = -2e6, hi = 2e6;
    for (int it = 0; it < 100; it++) {
        ld mid = (lo + hi) / 2;
        ld sum = 0;
        for (int i = 0; i < n; i++) {
            sum += pow(y[i] - mid * x[i] - b, 3);
        }
        if (sum > 0) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << setprecision(12);
    cout << (lo + hi) / 2 << "\n";

    return 0;
}