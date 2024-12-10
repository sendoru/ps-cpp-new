// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, x, k;
    cin >> n >> x >> k;

    vector<vector<pll>> goods(n);
    for (int i = 0; i < n; i++) {
        ll p, u, c;
        cin >> p >> u >> c;
        c--;
        goods[c].push_back({p, u});
    }

    for (int i = 0; i < n; i++) {
        sort(goods[i].begin(), goods[i].end(), [](pll a, pll b) {
            return a.second > b.second;
        });
    }

    vector<ll> dp(x + 1, -1);
    dp[0] = 0;
    vector<ll> dp_prev = dp;

    vector<bool> updated(x + 1, 0);

    for (int i = 0; i < n; i++) {
        // knapsack
        for (int j = 0; j < goods[i].size(); j++) {
            ll p = goods[i][j].first;
            ll u = goods[i][j].second;
            for (int i = x - p; i >= 0; i--) {
                if (dp[i] == -1) {
                    continue;
                }
                if (dp_prev[i] + u + k > dp[i + p]) {
                    dp[i + p] = dp_prev[i] + u + k;
                }
                if (dp[i] + u > dp[i + p]) {
                    dp[i + p] = dp[i] + u;
                }
            }
        }

        updated = vector<bool>(x + 1, 0);
        dp_prev = dp;
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
}
