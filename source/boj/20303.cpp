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
    vector<int> parent, size, weight;
    Dsu(int n) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    Dsu(int n, vector<int> &c) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
        for (int i = 0; i < n; i++) {
            weight.push_back(c[i]);
        }
    }
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        weight[x] += weight[y];
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int get_size(int x) {
        return size[find(x)];
    }
    int get_weight(int x) {
        return weight[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    Dsu dsu(n, c);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        dsu.unite(u, v);
    }

    vector<pll> cost_value;
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i) {
            cost_value.push_back({dsu.get_size(i), dsu.get_weight(i)});
        }
    }

    vector<ll> dp(k, -1);
    dp[0] = 0;
    for (auto [cost, value] : cost_value) {
        for (int j = k - 1; j >= cost; j--) {
            if (dp[j - cost] != -1) {
                dp[j] = max(dp[j], dp[j - cost] + value);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}