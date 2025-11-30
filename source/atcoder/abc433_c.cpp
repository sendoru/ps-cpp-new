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

    string s;
    cin >> s;
    ll ans = 0;

    vector<pll> intv;

    for (int i = 0; i < s.size(); i++) {
        if (i == 0 || s[i] != s[i - 1]) {
            intv.push_back({s[i], 1});
        } else {
            intv.back().second++;
        }
    }

    for (int i = 1; i < intv.size(); i++) {
        if (intv[i].first == intv[i - 1].first + 1) {
            ans += min(intv[i].second, intv[i - 1].second);
        }
    }

    cout << ans << "\n";

    return 0;
}