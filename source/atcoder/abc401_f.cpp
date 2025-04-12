// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> bfs(vector<vector<int>> &adj, int start)
{
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist;
}

vector<int> get_fartherst(vector<vector<int>> &adj)
{
    // get the farthest node from 0
    vector<int> dist = bfs(adj, 0);
    int farthest = max_element(dist.begin(), dist.end()) - dist.begin();
    // get the farthest node from the farthest node
    dist = bfs(adj, farthest);
    int farthest2 = max_element(dist.begin(), dist.end()) - dist.begin();
    // get the distance from the first end of diameter
    vector<int> dist1 = bfs(adj, farthest);
    // get the distance from the second end of diameter
    vector<int> dist2 = bfs(adj, farthest2);
    vector<int> ans(dist.size());
    for (int i = 0; i < dist.size(); i++) {
        ans[i] = max(dist1[i], dist2[i]);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n1;
    cin >> n1;
    vector<vector<int>> adj1(n1);
    for (int i = 0; i < n1 - 1; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        adj1[s].push_back(e);
        adj1[e].push_back(s);
    }
    vector<int> dist1 = get_fartherst(adj1);

    int n2;
    cin >> n2;
    vector<vector<int>> adj2(n2);
    for (int i = 0; i < n2 - 1; i++) {
        int s, e;
        cin >> s >> e;
        s--;
        e--;
        adj2[s].push_back(e);
        adj2[e].push_back(s);
    }
    vector<int> dist2 = get_fartherst(adj2);

    ll max_dist = *max_element(dist1.begin(), dist1.end());
    max_dist = max(max_dist, (ll)*max_element(dist2.begin(), dist2.end()));

    sort(dist1.begin(), dist1.end());
    sort(dist2.begin(), dist2.end());

    ll ans = 0;
    vector<ll> dist2_pf(n2);
    dist2_pf[0] = dist2[0];
    for (int i = 1; i < n2; i++) {
        dist2_pf[i] = dist2_pf[i - 1] + dist2[i];
    }
    for (int i = 0; i < n1; i++) {
        ll target = max_dist - dist1[i] - 1;
        auto it = upper_bound(dist2.begin(), dist2.end(), target);
        if (it == dist2.begin()) {
            ans += (ll)n2 * (dist1[i] + 1) + dist2_pf.back();
        }
        else {
            ans += max_dist * (it - dist2.begin());
            ans += (dist1[i] + 1) * ((ll)n2 - (it - dist2.begin()));
            ans += dist2_pf.back() - dist2_pf[it - dist2.begin() - 1];
        }
    }

    cout << ans << '\n';

    return 0;
}