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

    ll n, s;
    cin >> n >> s;
    vector<array<ll, 2>> arr;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll a, k;
        cin >> a >> k;
        arr.push_back({k, a / k});
        if (a % k) {
            arr.push_back({a % k, 1});
        }
        ans += a;
    }

    sort(arr.begin(), arr.end(), greater<>());

    for (auto [da, cnt] : arr) {
        if (s <= 0) {
            break;
        }
        if (s < cnt) {
            ans -= da * s;
            break;
        }
        ans -= da * cnt;
        s -= cnt;
    }

    cout << ans;

    return 0;
}