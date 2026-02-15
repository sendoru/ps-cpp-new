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
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<array<int, 2>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cur = 1000 * i + j;
            if (grid[i][j] == 'E') {
                edges.push_back({cur, cur + 1});
            } else if (grid[i][j] == 'W') {
                edges.push_back({cur, cur - 1});
            } else if (grid[i][j] == 'S') {
                edges.push_back({cur, cur + 1000});
            } else {
                edges.push_back({cur, cur - 1000});
            }
        }
    }

    Dsu dsu(1'000'000);
    for (auto [a, b] : edges) {
        dsu.unite(a, b);
    }
    set<int> roots;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cur = 1000 * i + j;
            roots.insert(dsu.find(cur));
        }
    }

    cout << roots.size();

    return 0;
}