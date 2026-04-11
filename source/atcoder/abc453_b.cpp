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

    ll t, x;
    cin >> t >> x;
    vector<ll> a(t + 1);
    for (int i = 0; i <= t; i++) {
        cin >> a[i];
    }

    vector<array<ll, 2>> ans;
    ans.push_back({0, a[0]});
    for (int i = 1; i <= t; i++) {
        if (abs(ans.back()[1] - a[i]) >= x) {
            ans.push_back({i, a[i]});
        }
    }

    for (auto &[i, v] : ans) {
        cout << i << ' ' << v << '\n';
    }

    return 0;
}