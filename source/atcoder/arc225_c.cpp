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
    vector<int> parent;
    vector<int> size;
    int n;

    Dsu(int n) : n(n) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<array<int, 4>> edges(m);
        for (int i = 0; i < m; i++) {
            cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
            edges[i][1]--;
            edges[i][2]--;
            edges[i][3] = i;
        }

        sort(edges.begin(), edges.end());
        vector<bool> used(m, 0);
        int min_w = 0, max_w = 0;
        Dsu dsu_min(n), dsu_max(n);
        for (auto [w, u, v, idx] : edges) {
            if (!dsu_min.same(u, v)) {
                dsu_min.unite(u, v);
                min_w += w;
                used[idx] = true;
            }
        }
        reverse(edges.begin(), edges.end());
        for (auto [w, u, v, _] : edges) {
            if (!dsu_max.same(u, v)) {
                dsu_max.unite(u, v);
                max_w += w;
            }
        }

        if (k < min_w || k > max_w) {
            cout << -1 << '\n';
            continue;
        }

        vector<array<int, 4>> edges_new;
        for (auto [w, u, v, idx] : edges) {
            if (used[idx] && w == 1) {
                edges_new.push_back({w, u, v, idx});
            }
        }
        for (auto [w, u, v, idx] : edges) {
            if (!used[idx] && w == 1) {
                edges_new.push_back({w, u, v, idx});
            }
        }
        for (auto [w, u, v, idx] : edges) {
            if (w == 0) {
                edges_new.push_back({w, u, v, idx});
            }
        }

        vector<int> ans;
        int cur_w = 0;
        Dsu dsu(n);
        for (auto [w, u, v, i] : edges_new) {
            if (cur_w == k && w == 1) {
                continue;
            }
            if (!dsu.same(u, v)) {
                dsu.unite(u, v);
                cur_w += w;
                ans.push_back(i);
            }
        }

        assert(cur_w == k);
        for (auto idx : ans) {
            cout << idx + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}