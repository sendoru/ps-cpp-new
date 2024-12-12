// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll HASH_BASE = 31;

ll get_tree_hash(vector<ll> &tree_hash, ll hash_base, vector<vector<int>> &adj_list, int node) {
    ll hash = 1;
    for (int child : adj_list[node]) {
        hash += hash_base * get_tree_hash(tree_hash, hash_base, adj_list, child);
        hash %= MOD1;
    }
    return tree_hash[node] = hash;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj_list(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int p, c;
        cin >> p >> c;
        adj_list[p].push_back(c);
    }

    vector<ll> tree_hash_31(n + 1), tree_hash_37(n + 1);
    get_tree_hash(tree_hash_31, 31, adj_list, 1);
    get_tree_hash(tree_hash_37, 37, adj_list, 1);
    map<pair<ll, ll>, int> hash_map;
    for (int i = 1; i <= n; i++) {
        hash_map[{tree_hash_31[i], tree_hash_37[i]}]++;
    }

    ll ans = 0;
    for (auto [key, val] : hash_map) {
        ans += (ll)val * (val - 1) / 2;
    }

    cout << ans << '\n';

    return 0;
}