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

    ll n, k;
    cin >> n >> k;
    if (n < k) {
        cout << 1 << '\n';
        return 0;
    }
    vector<ll> a(n + 1);
    for (int i = 0; i < k; i++) {
        a[i] = 1;
    }
    ll cur = k;
    for (int i = k; i <= n; i++) {
        a[i] = cur;
        cur -= a[i - k];
        cur += a[i] + 1e9;
        cur %= ll(1e9);
    }

    cout << a[n] << '\n';

    return 0;
}