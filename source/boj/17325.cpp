// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_subtree_sizes(const vector<vector<int>> &tree, int root) {
    int n = (int)tree.size();
    vector<int> sizes(n, 0);
    function<int(int)> dfs = [&](int node) {
        sizes[node] = 1;
        for (int child : tree[node]) {
            if (sizes[child] == 0) {
                sizes[node] += dfs(child);
            }
        }
        return sizes[node];
    };
    dfs(root);
    return sizes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<vector<int>> tree(n);
    vector<array<int, 3>> edges(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--;
        edges[i] = {u, v, c};
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    vector<int> sizes = get_subtree_sizes(tree, 0);
    ll ans = 0;

    for (auto edge : edges) {
        int u = edge[0], v = edge[1];
        ll c = edge[2];
        ans += c * abs(n - 2ll * min(sizes[u], sizes[v]));
    }

    cout << ans << '\n';

    return 0;
}