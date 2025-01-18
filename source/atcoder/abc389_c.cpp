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

    ll q;
    cin >> q;
    deque<pll> a;
    ll head = 0;
    while (q--) {
        ll x;
        cin >> x;
        if (x == 1) {
            ll l;
            cin >> l;
            if (a.empty()) {
                a.push_back({head, l});
            } else {
                a.push_back({a.back().first + a.back().second, l});
            }
        } else if (x == 2) {
            head += a.front().second;
            a.pop_front();
        } else {
            ll k;
            cin >> k;
            cout << a[k - 1].first - head << endl;
        }
    }

    return 0;
}