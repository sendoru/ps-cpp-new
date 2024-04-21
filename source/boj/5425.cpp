#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll get_digit_cnt(ll n, ll digit)
{
    if (n == 0)
        return 0;
    ll ret = 0;
    for (ll exp = 0, divider = 1; divider <= n; divider *= 10, exp++) {
        ll cur_digit = (n / divider) % 10;
        if (digit < cur_digit)
            ret += divider;
        else if (digit == cur_digit)
            ret += n % divider + 1;
        ret += cur_digit * exp * (divider / 10);
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        ll ans = 0;
        for (int i = 0; i < 10; i++)
            ans += (get_digit_cnt(b, i) - get_digit_cnt(a - 1, i)) * i;
        cout << ans << '\n';
    }

    return 0;
}