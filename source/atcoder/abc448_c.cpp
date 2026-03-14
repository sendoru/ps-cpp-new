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
    multiset<ll> a_set;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a_set.insert(a[i]);
    }
    while (q--) {
        ll k;
        cin >> k;
        vector<ll> b(k);
        for (int i = 0; i < k; i++) {
            cin >> b[i];
            b[i]--;
        }
        for (auto i : b) {
            a_set.erase(a_set.find(a[i]));
        }
        cout << *a_set.begin() << '\n';
        for (auto i : b) {
            a_set.insert(a[i]);
        }
    }

    return 0;
}