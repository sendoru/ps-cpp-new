// #include "atcoder/all"
#pragma GCC optimize("Ofast")
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
        vector<pll> r(n);
        for (ll i = 0; i < n; i++) {
            cin >> r[i].first;
            r[i].second = i;
        }

        vector<ll> bound(n, 1e12);
        sort(r.begin(), r.end());
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        for (ll i = 0; i < n; i++) {
            pq.push(r[i]);
        }
        while (!pq.empty()) {
            auto [row, idx] = pq.top();
            pq.pop();
            if (row > bound[idx]) {
                continue;
            }
            bound[idx] = row;
            if (idx - 1 >= 0) {
                if (bound[idx - 1] > row + 1) {
                    bound[idx - 1] = row + 1;
                    pq.push({row + 1, idx - 1});
                }
            }
            if (idx + 1 < n) {
                if (bound[idx + 1] > row + 1) {
                    bound[idx + 1] = row + 1;
                    pq.push({row + 1, idx + 1});
                }
            }
        }
        ll ans = 0;
        for (ll i = 0; i < n; i++) {
            auto [row, idx] = r[i];
            ans += row - bound[idx];
        }

        cout << ans << '\n';
    }

    return 0;
}