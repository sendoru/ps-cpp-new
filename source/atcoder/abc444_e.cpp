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

    ll n, d;
    cin >> n >> d;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    multiset<ll> s;
    ll ans = 0;
    for (int l = 0, r = 0; r < n; r++) {
        while (true) {
            auto it1 = s.upper_bound(a[r]), it2 = s.lower_bound(a[r]);
            bool l1 = (it1 != s.begin() && *prev(it1) > a[r] - d);
            bool l2 = (it2 != s.end() && *it2 < a[r] + d);
            if (l1 || l2) {
                s.erase(s.find(a[l]));
                l++;
            } else {
                break;
            }
        }
        s.insert(a[r]);
        ans += r - l + 1;
    }

    cout << ans << "\n";

    return 0;
}