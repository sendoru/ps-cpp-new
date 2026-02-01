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

vector<ll> get_min_move_res(const vector<pll> &r, ll diff) {
    ll n = r.size();
    vector<ll> bound(n, 1e12);
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
            if (bound[idx - 1] > row + diff) {
                bound[idx - 1] = row + diff;
                pq.push({row + diff, idx - 1});
            }
        }
        if (idx + 1 < n) {
            if (bound[idx + 1] > row + diff) {
                bound[idx + 1] = row + diff;
                pq.push({row + diff, idx + 1});
            }
        }
    }
    return bound;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, t;
    cin >> n >> t;
    vector<pll> r(n);
    for (ll i = 0; i < n; i++) {
        cin >> r[i].first;
        r[i].second = i;
    }

    ll l = 0, h = 1e9;
    ll min_move = 1e18;
    vector<ll> ans;
    while (l < h) {
        ll mid = (l + h) / 2;
        auto res = get_min_move_res(r, mid);
        ll cur_move = 0;
        for (int i = 0; i < n; i++) {
            cur_move += abs(res[i] - r[i].first);
        }
        if (cur_move <= t) {
            min_move = mid;
            ans = res;
            h = mid;
        } else {
            l = mid + 1;
        }
    }

    for (auto &elem : ans) {
        cout << elem << ' ';
    }

    return 0;
}