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
    vector<ll> a(n);
    vector<ll> pow(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ll pow_add = 0;
        while ((1 << pow_add) * a[i] < a[i - 1]) {
            pow_add++;
        }
        ll pow_minus = 0;
        while ((1 << (pow_minus + 1)) * a[i - 1] <= a[i]) {
            pow_minus++;
        }
        pow[i] = max(0ll, pow[i - 1] + pow_add - pow_minus);
        ans += pow[i];
    }

    cout << ans;

    return 0;
}