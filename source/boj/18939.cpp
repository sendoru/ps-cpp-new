#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;
        if ((n <= 2 * k - 1 && m <= 2 * k - 1) || m * n % 2 != 0) {
            cout << "Yuto\n";
        }
        else {
            cout << "Platina\n";
        }
    }

    return 0;
}