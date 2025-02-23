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

    vector<ll> v(100'001);
    v[1] = 1;
    for (int i = 3; i <= 100'000; i += 2) {
        v[i] = i;
    }
    ll n, m;
    cin >> n >> m;

    while (!(n == 0 && m == 0)) {
        if (n < m) {
            swap(n, m);
        }
        ll to = (m - 1) / 2;
        ll sum_cube = (to * (to + 1) / 2) * (to * (to + 1) / 2);
        ll sum_square = (to * (to + 1) * (2 * to + 1)) / 6;
        ll sum_linear = (to * (to + 1)) / 2;

        ll ans = 8 * sum_cube + 4 * (1 - n - m) * sum_square + 2 * (n * m - n - m) * sum_linear + m * n * (to + 1);

        cout << ans << '\n';

        cin >> n >> m;
    }

    return 0;
}