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

    int T;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        ll n, pd, pg;
        cin >> n >> pd >> pg;

        if ((pg == 100 && pd != 100) || (pg == 0 && pd != 0)) {
            cout << "Case #" << t << ": Broken" << endl;
            continue;
        }
        if ((pg == 100 && pd == 100) || (pg == 0 && pd == 0)) {
            cout << "Case #" << t << ": Possible" << endl;
            continue;
        }

        int g_min = 100 / __gcd(100ll, pd);
        if (g_min <= n) {
            cout << "Case #" << t << ": Possible" << endl;
        } else {
            cout << "Case #" << t << ": Broken" << endl;
        }
    }

    return 0;
}