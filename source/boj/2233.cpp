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
    string s;
    cin >> s;

    int i1, i2;
    cin >> i1 >> i2;
    i1--;
    i2--;

    int node_idx;
    vector<int> route_to_node(2 * n);
    vector<array<int, 2>> node_to_route(2 * n);
    vector<vector<int>> adj(n);
    stack<int> st;
    for (int i = 0; i < 2 * n; i++) {
        if (s[i] == '0') {
            route_to_node[i] = node_idx;
            node_to_route[node_idx][0] = i;
            st.push(node_idx);
            node_idx++;
        } else {
            int node = st.top();
            st.pop();
            route_to_node[i] = node;
            node_to_route[node][1] = i;
            if (!st.empty()) {
                adj[st.top()].push_back(node);
            }
        }
    }

    i1 = route_to_node[i1];
    i2 = route_to_node[i2];

    int min_cnt = MOD9, ans_node;
    for (int i = 0; i < n; i++) {
        vector<bool> visited(n);
        int cnt = 1;
        queue<int> q;
        q.push(i);
        visited[i] = true;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int next : adj[node]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                    cnt++;
                }
            }
        }
        if (visited[i1] && visited[i2] && cnt < min_cnt) {
            min_cnt = cnt;
            ans_node = i;
        }
    }

    cout << node_to_route[ans_node][0] + 1 << ' ' << node_to_route[ans_node][1] + 1 << '\n';

    return 0;
}