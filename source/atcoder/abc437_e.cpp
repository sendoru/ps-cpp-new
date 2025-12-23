// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct MultiTrie {
    vector<map<int, int>> trie;
    vector<int> translate;
    MultiTrie() {
        trie.push_back(map<int, int>());
        translate.push_back(0);
    }
    void append(int parent_idx, int val) {
        int trans_par_idx = translate[parent_idx];
        if (trie[trans_par_idx].count(val) == 0) {
            trie.push_back(map<int, int>());
            trie[trans_par_idx][val] = trie.size() - 1;
            translate.push_back(trie.size() - 1);
        } else {
            translate.push_back(trie[trans_par_idx][val]);
        }
    }
    vector<int> solve() {
        vector<int> res;
        vector<vector<int>> inverse(translate.size());
        for (int i = 0; i < translate.size(); i++) {
            inverse[translate[i]].push_back(i);
        }
        // dfs
        function<void(int)> dfs = [&](int node_idx) {
            for (auto idx : inverse[node_idx]) {
                res.push_back(idx);
            }
            for (auto &[_, child_idx] : trie[node_idx]) {
                dfs(child_idx);
            }
        };
        dfs(0);
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    MultiTrie mt;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mt.append(x, y);
    }
    vector<int> res = mt.solve();
    for (auto v : res) {
        if (v != 0) {
            cout << v << ' ';
        }
    }

    return 0;
}