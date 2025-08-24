#include "atcoder/all"
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
    Dsu(int n) : parent(n), size(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int a) {
        if (parent[a] == a)
            return a;
        return parent[a] = find(parent[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (parent[a] < parent[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    Dsu dsu(n);

    vector<bool> is_black(n, false);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            dsu.unite(a, b);
        } else if (t == 2) {
            int v;
            cin >> v;
            v--;
            int v_par = dsu.find(v);
            if (!is_black[v]) {
                dsu.size[v_par]++;
            } else {
                dsu.size[v_par]--;
            }
            is_black[v] = !is_black[v];
        } else {
            int v;
            cin >> v;
            v--;
            int v_par = dsu.find(v);
            cout << (dsu.size[v_par] > 0 ? "Yes" : "No") << "\n";
        }
    }

    return 0;
}