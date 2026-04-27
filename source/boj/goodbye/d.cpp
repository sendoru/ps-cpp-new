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
    int n;
    Dsu(int n) : parent(n), size(n, 1), n(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = find(parent[a]);
    }
    void merge(int a, int b) {
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
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<array<ll, 4>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--;
        edges[i][1]--;
        edges[i][3] = i;
    }
    sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) {
        return a[2] < b[2];
    });

    Dsu dsu(n);
    ll mst_cost = 0, mbst_cost = 0;
    for (int i = 0; i < m; i++) {
        if (!dsu.same(edges[i][0], edges[i][1])) {
            dsu.merge(edges[i][0], edges[i][1]);
            mst_cost += edges[i][2];
            mbst_cost = max(mbst_cost, edges[i][2]);
        }
    }
    while (edges.back()[2] > mbst_cost) {
        edges.pop_back();
    }
    reverse(edges.begin(), edges.end());
    Dsu dsu2(n);
    ll another_st_cost = 0;
    vector<ll> ans;
    for (int i = 0; i < (int)edges.size(); i++) {
        if (!dsu2.same(edges[i][0], edges[i][1])) {
            dsu2.merge(edges[i][0], edges[i][1]);
            another_st_cost += edges[i][2];
            ans.push_back(edges[i][3]);
        }
    }

    // all mst are mbst
    cout << "NO\n";

    if (mst_cost == another_st_cost) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < (int)ans.size(); i++) {
            cout << ans[i] + 1 << '\n';
        }
    }

    return 0;
}