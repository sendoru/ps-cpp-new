#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pll op_min(pll a, pll b) {
    return min(a, b);
}

pll op_max(pll a, pll b) {
    return max(a, b);
}

pll e_min() {
    return {LLONG_MAX, -1};
}

pll e_max() {
    return {LLONG_MIN, -1};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<pll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    // Bucket bucket(v);
    // for (int i = 0; i < q; i++) {
    //     int l, r;
    //     cin >> l >> r;
    //     l--;
    //     auto [min_val, min_idx] = bucket.get_min(l, r);
    //     auto [max_val, max_idx] = bucket.get_max(l, r);
    //     bucket.update(min_val, max_idx);
    //     bucket.update(max_val, min_idx);
    // }

    // for (int i = 0; i < n; i++) {
    //     cout << bucket.data[i] << " ";
    // }

    atcoder::segtree<pll, op_min, e_min> seg_min(v);
    atcoder::segtree<pll, op_max, e_max> seg_max(v);
    for (int i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;
        auto [min_val, min_idx] = seg_min.prod(l, r);
        auto [max_val, max_idx] = seg_max.prod(l, r);
        seg_min.set(max_idx, {min_val, max_idx});
        seg_min.set(min_idx, {max_val, min_idx});
        seg_max.set(max_idx, {min_val, max_idx});
        seg_max.set(min_idx, {max_val, min_idx});
    }

    for (int i = 0; i < n; i++) {
        cout << seg_min.get(i).first << " ";
    }

    return 0;
}