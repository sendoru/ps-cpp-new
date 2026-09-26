#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// {cnt, sum}
pll op_sum(pll a, pll b) {
    return {a.first + b.first, a.second + b.second};
}

pll e_sum() {
    return {0, 0};
}

struct Event {
    ll r, c, idx, sign;

    bool operator<(const Event &other) const {
        return c < other.c;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, q;
    cin >> n >> m >> q;

    vector<ll> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }

    vector<ll> ans(q);
    vector<Event> events;
    for (int i = 0; i < q; i++) {
        ll r1, c1, r2, c2;
        cin >> r1 >> r2 >> c1 >> c2;
        events.push_back({r2, c2, i, 1});
        if (r1 > 1) {
            events.push_back({r1 - 1, c2, i, -1});
        }
        if (c1 > 1) {
            events.push_back({r2, c1 - 1, i, -1});
        }
        if (r1 > 1 && c1 > 1) {
            events.push_back({r1 - 1, c1 - 1, i, 1});
        }
    }

    sort(events.begin(), events.end());
    vector<int> idx_by_l(n);
    iota(idx_by_l.begin(), idx_by_l.end(), 1);
    vector<int> idx_by_r(n);
    iota(idx_by_r.begin(), idx_by_r.end(), 1);
    sort(idx_by_l.begin(), idx_by_l.end(), [&](int a, int b) {
        return l[a] < l[b];
    });
    sort(idx_by_r.begin(), idx_by_r.end(), [&](int a, int b) {
        return r[a] < r[b];
    });

    atcoder::segtree<pll, op_sum, e_sum> seg_l(n + 2), seg_r(n + 2);
    int ptr_l = 0, ptr_r = 0;
    for (auto &event : events) {
        int c = event.c;
        while(ptr_l < n && l[idx_by_l[ptr_l]] <= c) {
            pll prev = seg_l.get(idx_by_l[ptr_l]);
            seg_l.set(idx_by_l[ptr_l], {prev.first + 1, prev.second + l[idx_by_l[ptr_l]]});
            ptr_l++;
        }
        while(ptr_r < n && r[idx_by_r[ptr_r]] < c) {
            pll prev = seg_r.get(idx_by_r[ptr_r]);
            seg_r.set(idx_by_r[ptr_r], {prev.first + 1, prev.second + r[idx_by_r[ptr_r]]});
            ptr_r++;
        }   

        auto [cnt_l, sum_l] = seg_l.prod(0, event.r + 1);
        auto [cnt_r, sum_r] = seg_r.prod(0, event.r + 1);
        
        ll total = cnt_l * (c + 1) - sum_l + sum_r - cnt_r * c;
        ans[event.idx] += event.sign * total;
    }

    for (auto &x : ans) {
        cout << x << "\n";
    }


    return 0;
}