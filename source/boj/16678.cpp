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
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a.push_back(0);
    sort(a.begin(), a.end());
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            ans += a[i] - a[i - 1] - 1;
            a[i] = a[i - 1] + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}