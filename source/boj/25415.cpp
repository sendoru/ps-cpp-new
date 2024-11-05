#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2")
#include <iostream>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll x[2002], y[2002];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    ll a, b, t, xx, yy, s;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    int ans = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            t = x[i] * y[j] - x[j] * y[i];
            xx = x[j] - x[i];
            yy = y[i] - y[j];
            for (int k = j + 1; k < n; k++) {
                s = abs(
                    t + xx * y[k] + yy * x[k]);
                ans += s >= a && s <= b;
            }
        }
    }
    cout << ans;
    return 0;
}