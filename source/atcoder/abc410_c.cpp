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

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    iota(a.begin(), a.end(), 1);
    ll start_idx = 0;

    for (int i = 0; i < q; i++) {
        ll qt;
        cin >> qt;
        if (qt == 1) {
            ll p, x;
            cin >> p >> x;
            p--;
            a[(p + start_idx) % n] = x;
        } else if (qt == 2) {
            ll p;
            cin >> p;
            p--;
            cout << a[(p + start_idx) % n] << "\n";
        } else {
            ll k;
            cin >> k;
            start_idx = (start_idx + k) % n;
        }
    }

    return 0;
}