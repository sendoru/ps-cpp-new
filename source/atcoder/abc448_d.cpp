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

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> a_unique = a;
    sort(a_unique.begin(), a_unique.end());
    a_unique.erase(unique(a_unique.begin(), a_unique.end()), a_unique.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(a_unique.begin(), a_unique.end(), a[i]) - a_unique.begin();
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dup_cnt = 0;
    vector<int> cnts(a_unique.size());
    vector<int> ans(n);
    function<void(int, int)> dfs = [&](int u, int p) {
        cnts[a[u]]++;
        if (cnts[a[u]] == 2) {
            dup_cnt++;
        }
        ans[u] = dup_cnt;
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            dfs(v, u);
        }
        cnts[a[u]]--;
        if (cnts[a[u]] == 1) {
            dup_cnt--;
        }
    };
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << (ans[i] > 0 ? "Yes" : "No") << '\n';
    }

    return 0;
}