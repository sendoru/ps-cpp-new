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
    vector<vector<pii>> adj_list(n + 1);
    for (int s = 1; s <= n; s++) {
        int e, w;
        cin >> e >> w;
        adj_list[s].push_back({e, w});
        adj_list[e].push_back({s, w});
    }
    vector<int> dist(n + 1, -1);
    int ans = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (dist[i] != -1) {
            continue;
        }
        q.push(i);
        int cur_cc_size = 1;
        int cur_parity_sum = 0;
        // we only need to know the parity of distances
        // and it's guaranteed that the parity is constant regardless of route, if start and end are same
        dist[i] = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto [next, w] : adj_list[cur]) {
                if (dist[next] == -1) {
                    dist[next] = dist[cur] + w;
                    cur_parity_sum += (dist[next] & 1);
                    q.push(next);
                    cur_cc_size++;
                }
            }
        }

        ans += min(cur_parity_sum, cur_cc_size - cur_parity_sum);
    }

    cout << ans << '\n';

    return 0;
}