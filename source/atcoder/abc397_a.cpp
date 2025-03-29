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

    double x;
    cin >> x;
    ll xx = (ll)round(x * 10);

    if (xx >= 380) {
        cout << 1;
    }
    else if (xx >= 375) {
        cout << 2;
    }
    else {
        cout << 3;
    }

    return 0;
}