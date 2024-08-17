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
    int n;
    Dsu(int _n) : n(_n)
    {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u)
    {
        if (u == parent[u]) {
            return u;
        }
        return parent[u] = find(parent[u]);
    }
    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v) {
            return;
        }
        parent[u] = v;
    }
};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, t;
    cin >> n >> m >> t;
    vector<vector<int>> edges;
    for (int i = 0; i < m; i++) {
        int s, e, w;
        cin >> s >> e >> w;
        s--, e--;
        edges.push_back({s, e, w});
    }

    sort(edges.begin(), edges.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[2] < b[2];
    });

    ll ans = 0;
    Dsu dsu(n);
    for (int i = 0; i < m; i++) {
        int s = edges[i][0];
        int e = edges[i][1];
        int w = edges[i][2];
        if (dsu.find(s) != dsu.find(e)) {
            dsu.merge(s, e);
            ans += w;
        }
    }

    if (n != 1) {
        ans += (n - 2) * (n - 1) / 2 * t;
    }

    cout << ans;

    return 0;
}