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

    ll n, k;
    cin >> n >> k;
    vector<ll> pos(n);
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }
    sort(pos.begin(), pos.end());
    vector<ll> diff(n - 1);
    for (int i = 0; i < n - 1; i++) {
        diff[i] = pos[i + 1] - pos[i];
    }
    sort(diff.begin(), diff.end());
    ll ans = 0;
    for (int i = 0; i < n - k; i++) {
        ans += diff[i];
    }
    cout << ans << "\n";

    return 0;
}