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
    int _n;
    vector<int> par, sz;

    Dsu(int n) : _n(n), par(n), sz(n, 1) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x] == x)
            return x;
        return par[x] = find(par[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (sz[x] < sz[y])
            swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll a_max = *max_element(a.begin(), a.end());
    vector<vector<ll>> val_to_idx(a_max + 1);
    for (int i = 0; i < n; i++) {
        val_to_idx[a[i]].push_back(i);
    }

    Dsu dsu(n);
    int edge_cnt = 0;
    ll ans = 0;
    for (ll div = a_max; div >= 1 && edge_cnt < n - 1; div--) {
        int root_idx = -1;
        for (ll mul = div; mul <= a_max; mul += div) {
            for (ll idx : val_to_idx[mul]) {
                if (root_idx == -1) {
                    root_idx = idx;
                } else if (!dsu.same(root_idx, idx)) {
                    dsu.unite(root_idx, idx);
                    ans += div;
                    edge_cnt++;
                }
            }
        }
    }

    cout << ans;

    return 0;
}