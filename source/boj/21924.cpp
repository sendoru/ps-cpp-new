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

    ll n, m;
    cin >> n >> m;
    vector<array<ll, 3>> edges(m);
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
        ans += edges[i][0];
        edges[i][1]--;
        edges[i][2]--;
    }

    sort(edges.begin(), edges.end());
    Dsu dsu(n);
    ll cnt = 0;
    for (int i = 0; i < m; i++) {
        if (dsu.find(edges[i][1]) != dsu.find(edges[i][2])) {
            dsu.unite(edges[i][1], edges[i][2]);
            ans -= edges[i][0];
            cnt++;
        }
    }

    if (cnt != n - 1) {
        cout << -1;
    } else {
        cout << ans;
    }

    return 0;
}