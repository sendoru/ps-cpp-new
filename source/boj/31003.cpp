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
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<vector<int>> adj_list(n);
    vector<int> indeg(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (gcd(v[i], v[j]) > 1) {
                adj_list[i].push_back(j);
                indeg[j]++;
            }
        }
    }

    vector<int> ans;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            pq.push({v[i], i});
        }
    }

    while (!pq.empty()) {
        auto [val, idx] = pq.top();
        pq.pop();
        ans.push_back(val);
        for (int next : adj_list[idx]) {
            indeg[next]--;
            if (indeg[next] == 0) {
                pq.push({v[next], next});
            }
        }
    }

    for (auto x : ans) {
        cout << x << " ";
    }

    return 0;
}