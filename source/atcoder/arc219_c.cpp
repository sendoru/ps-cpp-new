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

    ll h, w;
    cin >> h >> w;

    ll n;
    cin >> n;

    map<ll, vector<ll>> rooms;
    for (ll i = 0; i < n; i++) {
        ll r, c;
        cin >> r >> c;
        r--;
        c--;
        rooms[r].push_back(c);
    }

    ll ans = 0;

    // simplest approach
    // c == 0인 엘리베이터만 이용
    for (auto &[_, v] : rooms) {
        sort(v.begin(), v.end());
        ans += 2 * v.back();
    }

    // c == 0이랑 c == w - 1 둘 다 이용
    if (rooms.size() >= 2) {
        vector<ll> costs;
        for (auto &[_, v] : rooms) {
            ll max_diff = v[0];
            for (ll i = 1; i < v.size(); i++) {
                max_diff = max(max_diff, v[i] - v[i - 1]);
            }
            max_diff = max(max_diff, w - 1 - v.back());
            costs.push_back(w - 1 - max_diff);
        }
        if (costs.size() % 2 == 1) {
            costs.push_back(0);
        }
        sort(costs.begin(), costs.end());
        ll cost_sum = accumulate(costs.begin(), costs.end(), 0LL);
        ll pop_cnt = 0;
        while (costs.size() >= 2) {
            for (ll i = 0; i < 2; i++) {
                cost_sum -= costs.back();
                costs.pop_back();
                pop_cnt++;
            }
            ans = min(ans, pop_cnt * (w - 1) + 2 * cost_sum);
        }
    }

    cout << ans;
    return 0;
}