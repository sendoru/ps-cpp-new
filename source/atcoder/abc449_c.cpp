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

    ll n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;

    vector<vector<ll>> pos(26);
    for (int i = 0; i < n; i++) {
        pos[s[i] - 'a'].push_back(i);
    }

    ll ans = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < pos[i].size(); j++) {
            ll idx = pos[i][j];
            auto bottom = lower_bound(pos[i].begin(), pos[i].end(), idx + l);
            auto top = upper_bound(pos[i].begin(), pos[i].end(), idx + r);
            ans += top - bottom;
        }
    }

    cout << ans;

    return 0;
}