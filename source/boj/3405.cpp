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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {

        int n;
        cin >> n;
        vector<vector<int>> d(n, vector<int>(n));
        vector<int> sum(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> d[i][j];
                d[i][j] = -d[i][j];
                sum[i] += d[i][j];
            }
        }

        vector<bool> reachable((1 << n));

        function<void(int)> dfs = [&](int mask) {
            reachable[mask] = true;
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0 || sum[i] >= 0 || reachable[mask ^ (1 << i)]) {
                    continue;
                }
                for (int j = 0; j < n; j++) {
                    sum[j] += d[i][j];
                }
                dfs(mask ^ (1 << i));
                for (int j = 0; j < n; j++) {
                    sum[j] -= d[i][j];
                }
            }
        };

        dfs((1 << n) - 1);
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (reachable[1 << i]) {
                ans.push_back(i + 1);
            }
        }

        if (ans.empty()) {
            cout << "0\n";
        } else {
            for (auto &v : ans) {
                cout << v << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}