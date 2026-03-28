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
    int n;
    vector<int> root, size, parity_sum, parity_from_root;
    // this should be okay with small to large merge
    vector<set<int>> members;
    Dsu(int n) : n(n), root(n), size(n, 1), parity_sum(n), parity_from_root(n) {
        iota(root.begin(), root.end(), 0);
        size.assign(n, 1);
        parity_sum.assign(n, 0);
        parity_from_root.assign(n, 0);
        members.resize(n);
        for (int i = 0; i < n; i++) {
            members[i].insert(i);
        }
    }
    int find(int x) {
        if (root[x] == x) {
            return x;
        }
        return root[x] = find(root[x]);
    }
    int get_parity_from_root(int x) {
        int rx = find(x);
        if (rx == x) {
            return parity_from_root[x];
        }
        return parity_from_root[x] = get_parity_from_root(root[x]) ^ parity_from_root[x];
    }
    int get_size(int x) {
        return size[find(x)];
    }
    int get_parity_sum(int x) {
        return parity_sum[find(x)];
    }
    bool mergeable(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) {
            return get_parity_from_root(x) != get_parity_from_root(y);
        }
        return true;
    }
    void merge(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) {
            return;
        }
        if (size[rx] < size[ry]) {
            swap(x, y);
            swap(rx, ry);
        }
        root[ry] = rx;
        size[rx] += size[ry];
        int parity_x = get_parity_from_root(x);
        int parity_y = get_parity_from_root(y);
        // simple merge when differnet parity
        if (parity_x != parity_y) {
            parity_sum[rx] += parity_sum[ry];
        }
        // merge with parity change when same parity
        else {
            parity_sum[rx] += size[ry] - parity_sum[ry];
            // parity_from_root[ry] ^= 1;
            for (int elem : members[ry]) {
                parity_from_root[elem] ^= 1;
            }
        }
        members[rx].merge(members[ry]);
        members[ry].clear();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;

    Dsu dsu(n);
    int ans = 0;
    bool impossible = false;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        if (!dsu.mergeable(u, v)) {
            impossible = true;
        } else if (dsu.find(u) != dsu.find(v)) {
            ans -= min(dsu.get_parity_sum(u), dsu.get_size(u) - dsu.get_parity_sum(u));
            ans -= min(dsu.get_parity_sum(v), dsu.get_size(v) - dsu.get_parity_sum(v));
            dsu.merge(u, v);
            ans += min(dsu.get_parity_sum(u), dsu.get_size(u) - dsu.get_parity_sum(u));
        }
        if (impossible) {
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}