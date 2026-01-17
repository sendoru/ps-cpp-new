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

    ll n, k, x;
    cin >> n >> k >> x;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    a.erase(a.end() - (n - k), a.end());
    reverse(a.begin(), a.end());
    ll ans = (n - k);
    ll cur = 0;
    for (int i = 0; i < a.size(); i++) {
        cur += a[i];
        if (cur >= x) {
            cout << ans + 1 << "\n";
            return 0;
        }
        ans++;
    }

    cout << -1 << "\n";

    return 0;
}