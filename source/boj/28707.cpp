// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int m;
    cin >> m;
    vector<array<int, 3>> op(m);
    for (int i = 0; i < m; i++) {
        cin >> op[i][0] >> op[i][1] >> op[i][2];
    }

    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<>> pq;
    pq.push({0, a});
    map<vector<int>, int> dist;
    dist[a] = 0;
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d > dist[v])
            continue;

        for (auto [l, r, c] : op) {
            l--;
            r--;
            auto nv = v;
            swap(nv[l], nv[r]);
            int nd = d + c;
            if (dist.find(nv) == dist.end() || dist[nv] > nd) {
                dist[nv] = nd;
                pq.push({nd, nv});
            }
        }
    }
    auto sorted = a;
    sort(sorted.begin(), sorted.end());
    if (dist.find(sorted) == dist.end())
        cout << -1 << "\n";
    else
        cout << dist[sorted] << "\n";
    return 0;
}