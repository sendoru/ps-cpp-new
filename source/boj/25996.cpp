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

    ll n, x;
    cin >> n >> x;

    vector<ld> v(n);
    ld power_sum = 0;
    for (ll i = 0; i < n; i++) {
        cin >> v[i];
        power_sum += v[i] * v[i];
    }

    if (power_sum == 0) {
        for (int i = 0; i < n; i++) {
            cout << 0 << " ";
        }
        return 0;
    }

    ld power_avg = power_sum / n;
    ld ratio = sqrt(x / power_avg);
    cout << fixed << setprecision(10);
    for (ll i = 0; i < n; i++) {
        cout << v[i] * ratio << " ";
    }

    return 0;
}