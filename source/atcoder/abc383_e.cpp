// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Edge {
    ll s, e, w;

    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

struct Dsu {
    vector<int> parent;
    vector<int> size;

    Dsu(int n)
    {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    Dsu(vector<int> size)
    {
        int n = size.size();
        parent.resize(n);
        this->size = size;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
    }

    void set_size(int x, int s)
    {
        size[find(x)] = s;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    int get_size(int x)
    {
        return size[find(x)];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].s >> edges[i].e >> edges[i].w;
    }

    vector<int> a_cnt(n + 1, 0), b_cnt(n + 1, 0);
    for (int i = 0; i < k; i++) {
        int ai;
        cin >> ai;
        a_cnt[ai]++;
    }
    for (int i = 0; i < k; i++) {
        int bi;
        cin >> bi;
        b_cnt[bi]++;
    }

    vector<Edge> mst_edges;
    ll ans = 0;
    sort(edges.begin(), edges.end());
    Dsu dsu_a(a_cnt), dsu_b(b_cnt);
    for (int i = 0; i < m; i++) {
        if (dsu_a.same(edges[i].s, edges[i].e)) {
            continue;
        }
        ll a_s_size = dsu_a.get_size(edges[i].s);
        ll a_e_size = dsu_a.get_size(edges[i].e);
        ll b_s_size = dsu_b.get_size(edges[i].s);
        ll b_e_size = dsu_b.get_size(edges[i].e);

        ll size_1 = min(a_s_size, b_e_size);
        ll size_2 = min(a_e_size, b_s_size);
        ans += max(size_1, size_2) * edges[i].w;

        dsu_a.unite(edges[i].s, edges[i].e);
        dsu_b.unite(edges[i].s, edges[i].e);

        dsu_a.set_size(edges[i].s, dsu_a.get_size(edges[i].s) - max(size_1, size_2));
        dsu_b.set_size(edges[i].s, dsu_b.get_size(edges[i].e) - max(size_1, size_2));

        mst_edges.push_back(edges[i]);
    }

    cout << ans << endl;

    return 0;
}