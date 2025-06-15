// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// is b contained in a?
bool is_contained(pii a, pii b) {
    return (a.first <= b.first && b.second <= a.second);
}

bool is_overlap(pii a, pii b) {
    return (a.first <= b.second && b.first <= a.second && !is_contained(a, b) && !is_contained(b, a));
}

struct dsu {
    vector<int> parent, size, l, r;

    dsu(vector<pii> &intervals) {
        int n = intervals.size();
        parent.resize(n);
        size.resize(n, 1);
        l.resize(n);
        r.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            l[i] = intervals[i].first;
            r[i] = intervals[i].second;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (is_overlap(intervals[i], intervals[j])) {
                    unite(i, j);
                }
            }
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            // minimize parent
            if (y < x) {
                swap(x, y);
            }
            parent[y] = x;
            size[x] += size[y];
            l[x] = min(l[x], l[y]);
            r[x] = max(r[x], r[y]);
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pii> intervals(n);
        for (int i = 0; i < n; i++) {
            cin >> intervals[i].first >> intervals[i].second;
        }

        // if a is conainted in b, add directed edge from a to b
        // we will do topological sort later, using priority queue
        vector<vector<int>> adj_list(n);
        vector<int> in_degree(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (is_contained({intervals[i].first, intervals[i].second}, {intervals[j].first, intervals[j].second})) {
                    adj_list[i].push_back(j);
                    in_degree[j]++;
                } else if (is_contained({intervals[j].first, intervals[j].second}, {intervals[i].first, intervals[i].second})) {
                    adj_list[j].push_back(i);
                    in_degree[i]++;
                }
            }
        }

        // prioritize greater node
        priority_queue<int> pq;
        for (int i = 0; i < n; i++) {
            if (in_degree[i] == 0) {
                pq.push(i);
            }
        }

        vector<int> topological_order;
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            topological_order.push_back(u);
            for (int v : adj_list[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    pq.push(v);
                }
            }
        }

        int cur = n - 1;
        vector<int> result(n, -1);
        for (int node : topological_order) {
            result[node] = cur;
            cur--;
        }

        for (int i = 0; i < n; i++) {
            cout << result[i] + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}