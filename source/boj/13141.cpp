// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> min_dist(n, vector<int>(n, 1e9)), max_dist(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        min_dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int s, e, w;
        cin >> s >> e >> w;
        s--;
        e--;
        min_dist[s][e] = min(min_dist[s][e], w);
        min_dist[e][s] = min(min_dist[e][s], w);
        max_dist[s][e] = max(max_dist[s][e], w);
        max_dist[e][s] = max(max_dist[e][s], w);
    }

    for (int mid = 0; mid < n; mid++) {
        for (int s = 0; s < n; s++) {
            for (int e = 0; e < n; e++) {
                min_dist[s][e] = min(min_dist[s][e], min_dist[s][mid] + min_dist[mid][e]);
            }
        }
    }

    double ans = 1e9;
    for (int s = 0; s < n; s++) {
        double cur = 0;
        for (int e1 = 0; e1 < n; e1++) {
            for (int e2 = 0; e2 < n; e2++) {
                if (max_dist[e1][e2] == -1) {
                    continue;
                }
                cur = max(cur, (double)(min_dist[s][e1] + min_dist[s][e2] + max_dist[e1][e2]) / 2);
            }
        }
        ans = min(ans, cur);
    }

    cout << fixed << setprecision(1) << ans << '\n';

    return 0;
}