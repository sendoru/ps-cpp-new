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

    ll n;
    cin >> n;
    vector<pll> ab(n);
    for (ll i = 0; i < n; i++) {
        cin >> ab[i].first >> ab[i].second;
    }
    sort(ab.begin(), ab.end(), [&] (const pll& p1, const pll& p2) {
        if (p1.first != p2.first) {
            return p1.first < p2.first;
        }
        return p1.second > p2.second;
    });

    vector<ll> lis_stack;
    for (int i = 0; i < n; i++) {
        ll val = ab[i].second;
        auto it = lower_bound(lis_stack.begin(), lis_stack.end(), val);
        if (it == lis_stack.end()) {
            lis_stack.push_back(val);
        } else {
            *it = val;
        }
    }

    cout << lis_stack.size();

    return 0;
}