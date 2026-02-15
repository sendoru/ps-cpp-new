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
    vector<vector<array<ll, 3>>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        ll v1, v2, p, q;
        cin >> v1 >> v2 >> p >> q;
        adj[v1].push_back({v2, p, q});
        adj[v2].push_back({v1, q, p});
    }

    vector<pll> ans(n, {-1, -1});
    ans[0] = {1, 1};

    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int node = que.front();
        que.pop();
        for (auto [next, p, q] : adj[node]) {
            if (ans[next].first != -1) {
                continue;
            }
            ans[next].first = ans[node].first * q;
            ans[next].second = ans[node].second * p;
            ll g = gcd(ans[next].first, ans[next].second);
            ans[next].first /= g;
            ans[next].second /= g;
            que.push(next);
        }
    }

    ll num_gcd = 1;
    for (int i = 0; i < n; i++) {
        num_gcd = gcd(num_gcd, ans[i].first);
    }
    for (int i = 0; i < n; i++) {
        ans[i].first /= num_gcd;
    }
    ll den_lcm = 1;
    for (int i = 0; i < n; i++) {
        den_lcm = lcm(den_lcm, ans[i].second);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i].first * (den_lcm / ans[i].second) << " ";
    }

    return 0;
}