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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll momentum = 0;
        for (int i = 0; i < n; i++) {
            ll x;
            cin >> x;
            momentum += x;
        }
        if (momentum > 0) {
            cout << "Right" << endl;
        }
        else if (momentum < 0) {
            cout << "Left" << endl;
        }
        else {
            cout << "Equilibrium" << endl;
        }
    }

    return 0;
}