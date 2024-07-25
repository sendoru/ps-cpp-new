#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dinic {
    struct Edge {
        int to, cap, rev;
    };

    vector<vector<Edge>> graph;
    vector<int> level, iter;

    Dinic(int n) : graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, cap, (int)graph[to].size()});
        graph[to].push_back({from, 0, (int)graph[from].size() - 1});
    }

    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &e : graph[cur]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[cur] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(int cur, int t, int flow) {
        if (cur == t) {
            return flow;
        }
        for (int &i = iter[cur]; i < graph[cur].size(); i++) {
            auto &e = graph[cur][i];
            if (e.cap > 0 && level[cur] < level[e.to]) {
                int d = dfs(e.to, t, min(flow, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int ret = 0;
        while (true) {
            bfs(s);
            if (level[t] == -1) {
                break;
            }
            fill(iter.begin(), iter.end(), 0);
            while (true) {
                int flow = dfs(s, t, INT_MAX);
                if (flow == 0) {
                    break;
                }
                ret += flow;
            }
        }
        return ret;
    }
};

