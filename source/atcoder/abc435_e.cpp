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

// x: black count, y: white count
pii op(pii a, pii b) {
    return {a.x + b.x, a.y + b.y};
}

pii e() {
    return {0, 0};
}

pii mapping(int f, pii x) {
    if (f == 0) {
        return x;
    }
    return {x.x + x.y, 0};
}

int composition(int f, int g) {
    return max(f, g);
}

int id() {
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<pii> quries(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        // 0-based semi open
        l--;
        quries[i] = {l, r};
    }

    // compress
    vector<int> coords;
    coords.push_back(0);
    coords.push_back(n);
    for (auto [l, r] : quries) {
        coords.push_back(l);
        coords.push_back(r);
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    int m = (int)coords.size();
    vector<pii> v(m - 1);
    for (int i = 0; i < m - 1; i++) {
        int len = coords[i + 1] - coords[i];
        v[i] = {0, len}; // initially all white
    }
    for (int i = 0; i < q; i++) {
        int l = quries[i].x;
        int r = quries[i].y;
        quries[i].x = lower_bound(coords.begin(), coords.end(), l) - coords.begin();
        quries[i].y = lower_bound(coords.begin(), coords.end(), r) - coords.begin();
    }

    lazy_segtree<pii, op, e, int, mapping, composition, id> segtree(v);
    for (int i = 0; i < q; i++) {
        int l = quries[i].x;
        int r = quries[i].y;
        segtree.apply(l, r, 1);
        pii res = segtree.prod(0, m - 1);
        cout << res.y << "\n";
    }

    return 0;
}