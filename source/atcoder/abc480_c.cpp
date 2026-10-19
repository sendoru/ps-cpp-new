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

    ll n, k, t;
    cin >> n >> k >> t;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    while (!a.empty() && a.back() >= t) {
        a.pop_back();
    }
    n = a.size();
    ll ans = 0;
    ll till = 0;
    for (int i = 0; i < n; i++) {
        if (till < a[i]) {
            ans += (a[i] - till + k - 1) / k;
        }
        till = max(till, a[i] + k);
    }
    if (till < t) {
        ans += (t - till + k - 1) / k;
    }

    cout << ans;

    return 0;
}