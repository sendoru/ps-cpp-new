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

    ll H, W, h, w, n;
    cin >> H >> W >> h >> w >> n;
    vector<array<ll, 2>> rc(n);
    vector<array<ll, 3>> events(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> rc[i][0] >> rc[i][1];
        rc[i][0]--;
        rc[i][1]--;
        events[2 * i] = {rc[i][0], rc[i][1], 1};          // add
        events[2 * i + 1] = {rc[i][0] + h, rc[i][1], -1}; // remove
    }
    sort(events.begin(), events.end());

    multiset<ll> ms;
    ms.insert(-1);
    ms.insert(W);
    ll ans = (H - h + 1) * (W - w + 1);

    auto gap = [&](ll l, ll r) {
        return max(0LL, r - l - w);
    };
    ll occupied = 0;
    auto add = [&](ll c) {
        auto it = ms.lower_bound(c);
        ll r = *it;
        it--;
        ll l = *it;
        occupied -= gap(l, c) + gap(c, r) - gap(l, r);
        ms.insert(c);
    };

    auto del = [&](ll c) {
        auto it = ms.find(c);
        ll r = *next(it);
        ll l = *prev(it);
        occupied += gap(l, c) + gap(c, r) - gap(l, r);
        ms.erase(it);
    };
    ll pre_r = h - 1;
    for (int i = 0; i < 2 * n;) {
        ll cur_r = events[i][0];
        ll nxt_r = min(cur_r, H);
        if (pre_r < nxt_r) {
            ans -= occupied * (nxt_r - pre_r);
            pre_r = nxt_r;
        }
        while (i < 2 * n && events[i][0] == cur_r) {
            if (events[i][2] == 1) {
                add(events[i][1]);
            } else {
                del(events[i][1]);
            }
            i++;
        }
    }
    if (pre_r < H) {
        ans -= occupied * (H - pre_r);
    }
    cout << ans;

    return 0;
}