// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    vector<int> par, sz;
    Dsu(int n) : par(n), sz(n, 1) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int a) {
        if (par[a] == a)
            return a;
        return par[a] = find(par[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int size(int a) {
        return sz[find(a)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {w, u - 1, v - 1};
    }
    sort(edges.begin(), edges.end());

    auto lo = edges.begin(), hi = edges.end();
    vector<array<int, 3>> spanning;
    while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        Dsu dsu(n);
        vector<array<int, 3>> selected;
        for (auto it = mid; it != edges.end(); it++) {
            auto [w, u, v] = *it;
            if (!dsu.same(u, v)) {
                dsu.unite(u, v);
                selected.push_back(*it);
            }
        }
        if (dsu.size(0) == n) {
            spanning = selected;
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    ll ans = 0;
    sort(spanning.begin(), spanning.end(), greater<array<int, 3>>());
    Dsu dsu(n);
    for (auto [w, u, v] : spanning) {
        ans += (ll)w * dsu.size(u) * dsu.size(v);
        dsu.unite(u, v);
    }

    cout << ans << "\n";

    return 0;
}