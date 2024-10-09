// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<int>> mask_by_sum(23);

int solve(int n, vector<int> &v)
{
    int ret = 0;
    vector<int> reachable = {0};
    for (int i = 0; i < v.size(); i++) {
        vector<int> next_reachable;
        for (int cur_mask : reachable) {
            for (int added_mask : mask_by_sum[v[i]]) {
                int tmp = added_mask & ((1 << (n + 1)) - 1);
                if (tmp == added_mask && (cur_mask & added_mask) == 0) {
                    int next_mask = cur_mask | added_mask;
                    next_reachable.push_back(next_mask);
                    ret = max(ret, __builtin_popcount(next_mask));
                }
            }
        }
        sort(next_reachable.begin(), next_reachable.end());
        next_reachable.erase(unique(next_reachable.begin(), next_reachable.end()), next_reachable.end());
        swap(reachable, next_reachable);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 2; i < (1 << 23); i += 2) {
        int sum = 0;
        for (int j = 0; j <= 22; j++) {
            if (i & (1 << j)) {
                sum += j;
            }
        }
        if (sum < 23) {
            mask_by_sum[sum].push_back(i);
        }
    }

    int t = 1;
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }

        vector<int> v(m);
        for (int i = 0; i < m; i++) {
            cin >> v[i];
        }

        cout << "Game " << t << ": ";
        cout << solve(n, v) << "\n";
        t++;
    }
    return 0;
}