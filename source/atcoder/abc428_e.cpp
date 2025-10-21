// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_dists(vector<vector<int>> &adj_list, int s) {
    vector<int> dists(adj_list.size(), -1);
    dists[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj_list[u]) {
            if (dists[v] == -1) {
                dists[v] = dists[u] + 1;
                q.push(v);
            }
        }
    }

    return dists;
}

pii get_diameter_endpoints(vector<vector<int>> &adj_list) {
    pii res = {-1, -1};
    vector<int> dists = get_dists(adj_list, 0);
    // prioritize larger index
    int farthest = -1;
    for (int i = 0; i < dists.size(); i++) {
        if (farthest == -1 || dists[i] >= dists[farthest]) {
            farthest = i;
        }
    }
    res.first = farthest;
    dists = get_dists(adj_list, farthest);
    farthest = -1;
    for (int i = 0; i < dists.size(); i++) {
        if (farthest == -1 || dists[i] >= dists[farthest]) {
            farthest = i;
        }
    }
    res.second = farthest;
    if (res.first < res.second) {
        swap(res.first, res.second);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    pii diameter_ends = get_diameter_endpoints(adj_list);
    vector<int> dists_from_end1 = get_dists(adj_list, diameter_ends.first);
    vector<int> dists_from_end2 = get_dists(adj_list, diameter_ends.second);
    for (int i = 0; i < n; i++) {
        if (dists_from_end1[i] >= dists_from_end2[i]) {
            cout << diameter_ends.first + 1 << "\n";
        } else {
            cout << diameter_ends.second + 1 << "\n";
        }
    }

    return 0;
}