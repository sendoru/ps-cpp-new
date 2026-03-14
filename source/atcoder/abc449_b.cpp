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

    int h, w, q;
    cin >> h >> w >> q;
    while (q--) {
        int qt, cnt;
        cin >> qt >> cnt;
        if (qt == 1) {
            cout << w * cnt << "\n";
            h -= cnt;
        } else {
            cout << h * cnt << "\n";
            w -= cnt;
        }
    }

    return 0;
}