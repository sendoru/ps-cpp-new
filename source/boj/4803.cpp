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
    vector<int> parent, size;

    Dsu(int n) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = find(parent[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    int t = 1;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }

        Dsu dsu(n);
        vector<pii> edges(m);
        for (int i = 0; i < m; i++) {
            int v1, v2;
            cin >> v1 >> v2;
            v1--;
            v2--;
            dsu.unite(v1, v2);
            edges[i] = {v1, v2};
        }

        map<int, int> edge_cnt;
        for (int i = 0; i < m; i++) {
            edge_cnt[dsu.find(edges[i].first)]++;
        }
        for (int i = 0; i < n; i++) {
            if (edge_cnt.count(dsu.find(i)) == 0) {
                edge_cnt[dsu.find(i)] = 0;
            }
        }
        int tree_cnt = 0;
        for (auto &[root, cnt] : edge_cnt) {
            if (cnt == dsu.size[dsu.find(root)] - 1) {
                tree_cnt++;
            }
        }

        cout << "Case " << t << ": ";
        if (tree_cnt == 0) {
            cout << "No trees.\n";
        } else if (tree_cnt == 1) {
            cout << "There is one tree.\n";
        } else {
            cout << "A forest of " << tree_cnt << " trees.\n";
        }

        t++;
    }

    return 0;
}