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
        ll d, n, s, p;
        cin >> d >> n >> s >> p;
        ll par = d + n * p;
        ll ser = n * s;
        if (par < ser) {
            cout << "parallelize" << endl;
        }
        else if (par == ser) {
            cout << "does not matter" << endl;
        }
        else {
            cout << "do not parallelize" << endl;
        }
    }

    return 0;
}