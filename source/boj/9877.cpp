// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    vector<ll> parent, size, weight;
    Dsu(ll n) {
        parent.resize(n);
        size.resize(n, 1);
        weight.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    ll find(ll x) {
        if (parent[x] == x)
            return x;
        ll p = find(parent[x]);
        weight[x] += weight[parent[x]];
        return parent[x] = p;
    }
    bool same(ll x, ll y) {
        return find(x) == find(y);
    }
    void unite(ll x, ll y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        weight[x] += weight[y];
    }
    ll get_weight(ll x) {
        return weight[find(x)];
    }
    void set_weight(ll x, ll w) {
        weight[find(x)] = w;
    }
    ll get_size(ll x) {
        return size[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll r, c, t;
    cin >> r >> c >> t;
    vector<vector<ll>> grid(r, vector<ll>(c));
    for (ll i = 0; i < r; i++) {
        for (ll j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }
    vector<vector<int>> relevant(r, vector<int>(c, false));
    for (ll i = 0; i < r; i++) {
        for (ll j = 0; j < c; j++) {
            cin >> relevant[i][j];
        }
    }

    Dsu dsu(r * c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (relevant[i][j]) {
                dsu.set_weight(i * c + j, 1);
            }
        }
    }

    vector<tuple<ll, ll, ll>> edges;
    for (ll i = 0; i < r - 1; i++) {
        for (ll j = 0; j < c; j++) {
            edges.push_back({abs(grid[i][j] - grid[i + 1][j]), i * c + j, (i + 1) * c + j});
        }
    }
    for (ll i = 0; i < r; i++) {
        for (ll j = 0; j < c - 1; j++) {
            edges.push_back({abs(grid[i][j] - grid[i][j + 1]), i * c + j, i * c + (j + 1)});
        }
    }
    sort(edges.begin(), edges.end());
    ll ans = 0;
    for (auto [w, u, v] : edges) {
        if (!dsu.same(u, v)) {
            dsu.unite(u, v);
            ll par = dsu.find(u);
            if (dsu.get_size(par) >= t) {
                ans += w * dsu.get_weight(par);
                dsu.set_weight(par, 0);
            }
        }
    }

    cout << ans;

    return 0;
}