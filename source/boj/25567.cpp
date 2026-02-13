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
    vector<deque<int>> members;
    Dsu(int n) {
        parent.resize(n);
        members.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        } else {
            return parent[x] = find(parent[x]);
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        if (members[x].size() < members[y].size()) {
            while (!members[x].empty()) {
                members[y].push_front(members[x].back());
                members[x].pop_back();
            }
            parent[x] = y;
        } else {
            while (!members[y].empty()) {
                members[x].push_back(members[y].front());
                members[y].pop_front();
            }
            parent[y] = x;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    Dsu dsu(n);
    vector<int> item_to_group(200'010, -1);
    for (int i = 0; i < n; i++) {
        int cnt;
        cin >> cnt;
        dsu.members[i].resize(cnt);
        for (int j = 0; j < cnt; j++) {
            cin >> dsu.members[i][j];
            item_to_group[dsu.members[i][j]] = i;
        }
    }

    int q;
    cin >> q;
    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
    }

    vector<ll> ans(q, -1);
    for (int i = 0; i < q; i++) {
        int qt = queries[i][0];
        if (qt == 1) {
            int a = item_to_group[queries[i][1]];
            int b = item_to_group[queries[i][2]];
            if (dsu.same(a, b)) {
                ans[i] = 0;
            } else {
                ans[i] = 1;
                dsu.unite(a, b);
            }
        } else {
            int a = item_to_group[queries[i][1]];
            int b = item_to_group[queries[i][2]];
            if (dsu.same(a, b)) {
                ans[i] = 1;
            }
        }
    }

    vector<vector<ll>> prefix_sums(n);
    vector<int> order(200'010, -1);
    for (int i = 0; i < n; i++) {
        int p = dsu.find(i);
        if (i != p) {
            continue;
        }
        prefix_sums[p].resize(dsu.members[p].size() + 1);
        for (int j = 0; j < (int)dsu.members[p].size(); j++) {
            prefix_sums[p][j + 1] = prefix_sums[p][j] + dsu.members[p][j];
            order[dsu.members[p][j]] = j;
        }
    }

    for (int i = 0; i < q; i++) {
        if (queries[i][0] == 2 && ans[i] == 1) {
            int a = queries[i][1];
            int b = queries[i][2];
            int group = dsu.find(item_to_group[a]);
            int l = min(order[a], order[b]);
            int r = max(order[a], order[b]);
            ans[i] = prefix_sums[group][r + 1] - prefix_sums[group][l];
        }
    }

    for (int i = 0; i < q; i++) {
        if (queries[i][0] == 1) {
            cout << (ans[i] ? "YES\n" : "NO\n");
        } else {
            cout << ans[i] << "\n";
        }
    }

    return 0;
}