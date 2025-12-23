#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
using namespace atcoder;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pll op1(pll a, pll b) {
    if (a.first + a.second > b.first + b.second) {
        return a;
    } else {
        return b;
    }
}

pll op2(pll a, pll b) {
    if (a.first - a.second > b.first - b.second) {
        return a;
    } else {
        return b;
    }
}

pll op3(pll a, pll b) {
    if (-a.first + a.second > -b.first + b.second) {
        return a;
    } else {
        return b;
    }
}

pll op4(pll a, pll b) {
    if (-a.first - a.second > -b.first - b.second) {
        return a;
    } else {
        return b;
    }
}

pll e1() { return {-1e12, -1e12}; }
pll e2() { return {-1e12, 1e12}; }
pll e3() { return {1e12, -1e12}; }
pll e4() { return {1e12, 1e12}; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<pll> coord(n);
    for (int i = 0; i < n; i++) {
        cin >> coord[i].first >> coord[i].second;
    }

    segtree<pll, op1, e1> seg1(coord);
    segtree<pll, op2, e2> seg2(coord);
    segtree<pll, op3, e3> seg3(coord);
    segtree<pll, op4, e4> seg4(coord);

    while (q--) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            ll i, x, y;
            cin >> i >> x >> y;
            coord[i - 1] = {x, y};
            seg1.set(i - 1, {x, y});
            seg2.set(i - 1, {x, y});
            seg3.set(i - 1, {x, y});
            seg4.set(i - 1, {x, y});
        } else {
            ll l, r, x, y;
            cin >> l >> r >> x >> y;
            l--;
            vector<pll> cands;
            cands.push_back(seg1.prod(l, r));
            cands.push_back(seg2.prod(l, r));
            cands.push_back(seg3.prod(l, r));
            cands.push_back(seg4.prod(l, r));
            ll ans = 0;
            for (auto cand : cands) {
                ans = max(ans, abs(cand.first - x) + abs(cand.second - y));
            }
            cout << ans << "\n";
        }
    }

    return 0;
}