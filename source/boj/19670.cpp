// #include "atcoder/all"
#pragma GCC optimize("O3")
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

    Dsu(int n) : parent(n), size(n, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (size[x] < size[y]) {
                swap(x, y);
            }
            parent[y] = x;
            size[x] += size[y];
        }
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

    int n, q;
    cin >> n >> q;
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    ll h_max = *max_element(h.begin(), h.end());

    vector<pii> h_sorted(n);
    for (int i = 0; i < n; i++) {
        h_sorted[i] = {h[i], i};
    }

    sort(h_sorted.begin(), h_sorted.end());
    Dsu dsu(n);

    vector<ll> ans(h_max + 1, 0);
    vector<bool> visited(n, false);
    ll cur = 0;
    auto iter = h_sorted.begin();

    for (int i = 1; i <= h_max; i++) {
        while (iter != h_sorted.end() && iter->first <= i) {
            // merge left
            if ((*iter).second != 0 && h[(*iter).second - 1] <= i && visited[(*iter).second - 1]) {
                ll left_size = dsu.get_size((*iter).second - 1);
                cur -= left_size * (left_size + 1) / 2;
                dsu.unite((*iter).second, (*iter).second - 1);
            }
            // merge right
            if ((*iter).second != n - 1 && h[(*iter).second + 1] <= i && visited[(*iter).second + 1]) {
                ll right_size = dsu.get_size((*iter).second + 1);
                cur -= right_size * (right_size + 1) / 2;
                dsu.unite((*iter).second, (*iter).second + 1);
            }
            // add current
            ll cur_size = dsu.get_size((*iter).second);
            cur += cur_size * (cur_size + 1) / 2;
            visited[(*iter).second] = true;
            iter++;
        }
        ans[i] = cur;
    }

    for (int i = 0; i < q; i++) {
        ll x;
        cin >> x;
        cout << ans[min(x, h_max)] << '\n';
    }

    return 0;
}