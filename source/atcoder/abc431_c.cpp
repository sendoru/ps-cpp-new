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

    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> h(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(h.begin(), h.end());
    multiset<ll> bs;
    for (auto &x : b) {
        bs.insert(x);
    }

    for (int i = 0; i < k; i++) {
        auto it = bs.lower_bound(h[i]);
        if (it == bs.end()) {
            cout << "No";
            return 0;
        }
        bs.erase(it);
    }

    cout << "Yes";
    return 0;
}