// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // a[i] + i = j - a[j]
    map<ll, ll> mp1, mp2;
    for (int i = 0; i < n; i++) {
        mp1[a[i] + i]++;
        mp2[i - a[i]]++;
    }

    ll ans = 0;
    for (auto &[k, v] : mp1) {
        ans += v * mp2[k];
    }
    cout << ans << '\n';

    return 0;
}