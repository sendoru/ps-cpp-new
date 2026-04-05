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

    ll n, m, q;
    cin >> n >> m >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    multiset<ll> ls, rs;
    for (int i = 0; i < m; i++) {
        ll l;
        cin >> l;
        ls.insert(l - 1);
    }
    for (int i = 0; i < m; i++) {
        ll r;
        cin >> r;
        rs.insert(r - 1);
    }

    vector<array<ll, 2>> intervals;
    bool doomed = false;
    for (auto l : ls) {
        auto it = rs.lower_bound(l);
        if (it == rs.end()) {
            // doomed = true;
            // break;
            for (int i = 0; i < q; i++) {
                cout << (int)1e9 << "\n";
            }
            return 0;
        }
        intervals.push_back({l, *it});
        rs.erase(it);

        // merge intervals
        while (intervals.size() >= 2) {
            auto [cur_l, cur_r] = intervals.back();
            auto [prev_l, prev_r] = intervals[intervals.size() - 2];
            if (prev_r >= cur_l) {
                intervals.pop_back();
                intervals.pop_back();
                intervals.push_back({min(prev_l, cur_l), max(prev_r, cur_r)});
            } else {
                break;
            }
        }
    }

    vector<bool> mask(n, false);

    for (auto [l, r] : intervals) {
        for (int i = l; i <= r; i++) {
            mask[i] = true;
        }
    }

    multiset<ll> vals;
    for (int i = 0; i < n; i++) {
        if (mask[i]) {
            vals.insert(a[i]);
        }
    }

    while (q--) {
        int idx_1, idx_2;
        cin >> idx_1 >> idx_2;
        idx_1--;
        idx_2--;
        if (doomed) {
            cout << (int)1e9 << "\n";
            continue;
        }
        if (mask[idx_1]) {
            vals.erase(vals.find(a[idx_1]));
            vals.insert(a[idx_2]);
        }
        if (mask[idx_2]) {
            vals.erase(vals.find(a[idx_2]));
            vals.insert(a[idx_1]);
        }
        swap(a[idx_1], a[idx_2]);
        cout << *vals.rbegin() << "\n";
    }
    return 0;
}