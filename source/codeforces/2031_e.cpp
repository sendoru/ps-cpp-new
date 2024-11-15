// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int solve(vector<vector<int>> &adj_list, vector<int> &dp, int node) {
    if (adj_list[node].empty()) {
        dp[node] = 0;
        return 0;
    }

    vector<int> child_ans;
    for (int child : adj_list[node]) {
        child_ans.push_back(solve(adj_list, dp, child));
    }

    if (child_ans.size() <= 2) {
        dp[node] = *max_element(child_ans.begin(), child_ans.end()) + 1;
        return dp[node];
    }

    priority_queue<int, vector<int>, greater<>> pq;
    for (int ans : child_ans) {
        pq.push(ans);
    }
    while (pq.size() > 2) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        pq.push(max(a, b) + 1);
    }
    dp[node] = pq.top() + 1;
    pq.pop();
    dp[node] = max(dp[node], pq.top() + 1);
    return dp[node];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> par(n);
        for (int i = 1; i < n; i++) {
            cin >> par[i];
            par[i]--;
        }
        vector<vector<int>> adj_list(n);
        for (int i = 1; i < n; i++) {
            adj_list[par[i]].push_back(i);
        }
        vector<int> dp(n, -1);
        cout << solve(adj_list, dp, 0) << '\n';
    }

    return 0;
}