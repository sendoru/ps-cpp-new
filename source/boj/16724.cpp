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
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int get_size(int x) {
        return size[find(x)];
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

    Dsu dsu(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ni = i, nj = j;
            if (grid[i][j] == 'U') {
                ni--;
            } else if (grid[i][j] == 'D') {
                ni++;
            } else if (grid[i][j] == 'L') {
                nj--;
            } else if (grid[i][j] == 'R') {
                nj++;
            }
            dsu.unite(i * m + j, ni * m + nj);
        }
    }

    vector<bool> check(n * m, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            check[dsu.find(i * m + j)] = true;
        }
    }

    int ans = 0;
    for (int i = 0; i < n * m; i++) {
        if (check[i]) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}