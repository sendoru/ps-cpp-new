// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> par(n);
    vector<vector<int>> children(n);
    vector<int> val(n);
    int root;
    for (int i = 0; i < n; i++) {
        cin >> par[i];
        if (par[i] != -1) {
            par[i]--;
        } else {
            root = i;
            continue;
        }
        children[par[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    vector<int> depth(n, -1);
    vector<int> st_size(n, 1);

    function<void(int, int)> dfs = [&](int node, int d) {
        depth[node] = d;
        for (int child : children[node]) {
            dfs(child, d + 1);
            st_size[node] += st_size[child];
        }
    };
    dfs(root, 0);

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return depth[a] > depth[b];
    });

    for (auto &children_list : children) {
        sort(children_list.begin(), children_list.end(), [&](int a, int b) {
            return st_size[a] > st_size[b];
        });
    }

    vector<int> mex(n, 0);
    vector<set<int> *> nums(n, nullptr);

    for (auto v : order) {
        if (children[v].empty()) {
            nums[v] = new set<int>({val[v]});
            mex[v] = (val[v] == 0 ? 1 : 0);
        } else {
            int big_child = children[v][0];
            nums[v] = nums[big_child];
            mex[v] = mex[big_child];
            for (int i = 1; i < (int)children[v].size(); i++) {
                mex[v] = max(mex[v], mex[children[v][i]]);
                int c = children[v][i];
                for (int x : *nums[c]) {
                    nums[v]->insert(x);
                }
                delete nums[c];
            }
            nums[v]->insert(val[v]);
            while (nums[v]->count(mex[v])) {
                mex[v]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << mex[i] << '\n';
    }

    return 0;
}