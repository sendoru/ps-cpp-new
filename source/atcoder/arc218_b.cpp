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

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        map<ll, ll> cnt;
        for (int i = 0; i < n; i++) {
            ll a;
            cin >> a;
            cnt[a]++;
        }
        if (cnt.find(0) == cnt.end()) {
            cnt[0] = 0;
        }
        vector<ll> rocks;
        ll prev_k, prev_v;
        for (auto [k, v] : cnt) {
            if (k == 0) {
                if (v != 0) {
                    rocks.push_back(v);
                }
            } else {
                rocks.push_back(k - prev_k);
                rocks.push_back(v);
            }
            prev_k = k;
            prev_v = v;
        }
        vector<bool> dp(rocks.size());
        dp.back() = 1;
        for (int i = (int)rocks.size() - 2; i >= 0; i--) {
            if (rocks[i] == 1) {
                dp[i] = !dp[i + 1];
            } else {
                dp[i] = 1;
            }
        }

        if (dp[0]) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }

    return 0;
}