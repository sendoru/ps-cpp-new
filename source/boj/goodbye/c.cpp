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
    vector<array<ll, 3>> info(n);
    for (int i = 0; i < n; i++) {
        cin >> info[i][2] >> info[i][0] >> info[i][1];
    }
    sort(info.begin(), info.end(), [](const auto &a, const auto &b) {
        return a[2] < b[2];
    });
    while (info.back()[2] > d) {
        info.pop_back();
    }
    n = info.size();
    ll ans = 0;
    ll max_b = -1e18;
    for (int l = 0, r = n - 1; r >= 0; r--) {
        ans = max(ans, info[r][0] + info[r][1]);
        while (l < n && info[l][2] + info[r][2] <= d) {
            max_b = max(max_b, info[l][1]);
            l++;
        }
        if (max_b > -1e18) {
            ans = max(ans, info[r][0] + max_b);
        }
    }

    cout << ans;

    return 0;
}