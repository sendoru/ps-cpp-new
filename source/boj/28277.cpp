// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Sets {
    vector<int> idxs;
    vector<set<int>> members;
    Sets(int n) {
        idxs.resize(n);
        members.resize(n);
        for (int i = 0; i < n; i++) {
            idxs[i] = i;
        }
    }

    // x = x U y, y = empty
    void unite(int x, int y) {
        int x_idx = idxs[x];
        int y_idx = idxs[y];
        if (x == y) {
            return;
        }
        if (members[x_idx].size() > members[y_idx].size()) {
            for (int item : members[y_idx]) {
                members[x_idx].insert(item);
            }
            members[y_idx].clear();
        } else {
            for (int item : members[x_idx]) {
                members[y_idx].insert(item);
            }
            members[x_idx].clear();
            swap(idxs[x], idxs[y]);
        }
    }

    int get_size(int x) {
        return members[idxs[x]].size();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    Sets sets(n);
    for (int i = 0; i < n; i++) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++) {
            int item;
            cin >> item;
            sets.members[i].insert(item);
        }
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            sets.unite(a, b);
        } else {
            int a;
            cin >> a;
            a--;
            cout << sets.get_size(a) << "\n";
        }
    }

    return 0;
}