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

    int n;
    cin >> n;
    set<pll> s;
    s.insert({0, 0});
    vector<ll> min_dists = {0};
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ll cur = INT32_MAX;
        if (i == 1) {
            cur = abs(x - 0);
            min_dists[0] = cur;
            ans += cur;
        } else {
            auto it = s.lower_bound({x, -1});
            if (it != s.end()) {
                cur = abs(x - (*it).first);
                if (min_dists[(*it).second] > abs(x - (*it).first)) {
                    ans -= min_dists[(*it).second];
                    min_dists[(*it).second] = abs(x - (*it).first);
                    ans += abs(x - (*it).first);
                }
            }
            if (it != s.begin()) {
                --it;
                cur = min(cur, abs(x - (*it).first));
                if (min_dists[(*it).second] > abs(x - (*it).first)) {
                    ans -= min_dists[(*it).second];
                    min_dists[(*it).second] = abs(x - (*it).first);
                    ans += abs(x - (*it).first);
                }
            }
        }
        ans += cur;
        min_dists.push_back(cur);
        cout << ans << "\n";
        s.insert({x, i});
    }

    return 0;
}