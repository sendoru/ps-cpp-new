#include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
using namespace atcoder;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// {val, idx}
pii op(pii a, pii b) {
    return max(a, b);
}

pii e() {
    return {0, 0};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    vector<pii> seg_data(n);
    for (int i = 0; i < n; i++) {
        seg_data[i] = {p[i], i};
    }
    // max segtree with index
    segtree<pii, op, e> seg(n);
    for (int i = 0; i < n; i++) {
        seg.set(i, seg_data[i]);
    }

    function<ll(int, int)> solve = [&](int l, int r) -> ll {
        if (l >= r) {
            return 0;
        }
        auto [max_val, max_idx] = seg.prod(l, r);
        ll left_ans;
        if (max_idx > l) {
            left_ans = solve(l, max_idx);
            left_ans += abs(max_idx - seg.prod(l, max_idx).y);
        }
        else {
            left_ans = 0;
        }
        ll right_ans;
        if (max_idx + 1 < r) {
            right_ans = solve(max_idx + 1, r);
            right_ans += abs(max_idx - seg.prod(max_idx + 1, r).y);
        }
        else {
            right_ans = 0;
        }
        return max(left_ans, right_ans);
    };

    cout << solve(0, n) << "\n";

    return 0;
}