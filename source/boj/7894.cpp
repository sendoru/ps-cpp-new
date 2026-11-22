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

    int t;
    cin >> t;
    vector<ll> ans(1e7 + 1);
    double log10_fact = 0;
    for (ll i = 1; i <= 1e7; i++) {
        log10_fact += log10(i);
        ans[i] = (ll)floor(log10_fact) + 1;
    }

    while (t--) {
        ll n;
        cin >> n;
        cout << ans[n] << "\n";
    }

    return 0;
}