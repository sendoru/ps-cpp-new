// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct MaxSegTree {
    vector<ll> tree;
    int size;

    MaxSegTree() : size(0) {}

    MaxSegTree(int n) {
        size = 1;
        while (size < n) {
            size <<= 1;
        }
        tree.assign(2 * size, -1e9);
    }

    MaxSegTree(const vector<ll> &values) {
        int n = values.size();
        size = 1;
        while (size < n) {
            size <<= 1;
        }
        tree.assign(2 * size, -1e9);
        for (int i = 0; i < n; i++) {
            tree[size + i] = values[i];
        }
        for (int i = size - 1; i > 0; --i) {
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void update(int idx, ll value) {
        idx += size;
        tree[idx] = value;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    // semi-open interval [l, r)
    ll query(int l, int r) {
        l += size;
        r += size;
        ll res = -1e9;
        while (l < r) {
            if (l & 1) {
                res = max(res, tree[l++]);
            }
            if (r & 1) {
                res = max(res, tree[--r]);
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }

    ll query(int idx) {
        return tree[idx + size];
    }
};

// initializer: 간선 정보를 기반으로 트리를 구성
// query(int u, int v): u와 v 사이의 경로에서 최대값을 반환
// update(int idx, ll value): idx번째 간선의 가중치를 value로 업데이트
struct HLD {
    vector<int> parent, depth, size, in, out, chain_top, idx_to_node;
    vector<vector<int>> adj, adj_directed;
    vector<ll> edge_weights;
    MaxSegTree seg;

    HLD(const vector<vector<ll>> &edges) {
        int n = edges.size() + 1; // 간선 수 + 1
        adj.resize(n);
        adj_directed.resize(n);
        parent.resize(n, -1);
        depth.resize(n, 0);
        size.resize(n, 0);
        in.resize(n, 0);
        out.resize(n, 0);
        chain_top.resize(n, -1);
        edge_weights.resize(n, 0);

        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            ll weight = edges[i][2];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs0(0);
        dfs1(0);
        int order = 0;
        dfs2(0, order);

        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            ll weight = edges[i][2];
            if (depth[u] < depth[v]) {
                swap(u, v); // u가 자식
            }
            edge_weights[u] = weight;
            idx_to_node.push_back(u);
        }

        vector<ll> seg_base(n, -1e9);
        for (int i = 0; i < n - 1; i++) {
            seg_base[in[idx_to_node[i]]] = edge_weights[idx_to_node[i]];
        }
        seg = MaxSegTree(seg_base);
    }

    void dfs0(int v) {
        for (int &u : adj[v]) {
            if (u == parent[v])
                continue;
            adj_directed[v].push_back(u);
            parent[u] = v;
            depth[u] = depth[v] + 1;
            dfs0(u);
        }
    }

    void dfs1(int v) {
        size[v] = 1;
        for (int &u : adj_directed[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            dfs1(u);
            size[v] += size[u];
            if (size[u] > size[adj_directed[v][0]]) {
                swap(adj_directed[v][0], u); // 가장 큰 자식 노드를 첫 번째로 이동
            }
        }
    }

    void dfs2(int v, int &order) {
        in[v] = order++;
        for (int u : adj_directed[v]) {
            if (u == parent[v])
                continue;
            if (u == adj_directed[v][0]) {
                chain_top[u] = chain_top[v]; // 같은 체인에 속하는 경우
            } else {
                chain_top[u] = u; // 새로운 체인 시작
            }
            dfs2(u, order);
        }
        out[v] = order;
    }

    void update(int idx, ll val) {
        seg.update(in[idx_to_node[idx]], val);
    }

    ll query(int u, int v) {
        ll res = -1e9;
        while (chain_top[u] != chain_top[v]) {
            if (depth[chain_top[u]] < depth[chain_top[v]]) {
                swap(u, v);
            }
            res = max(res, seg.query(in[chain_top[u]], in[u] + 1));
            u = parent[chain_top[u]];
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        res = max(res, seg.query(in[u] + 1, in[v] + 1));
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<ll>> edges(n - 1, vector<ll>(3));
    for (int i = 0; i < n - 1; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--; // 0-indexed
        edges[i][1]--;
    }

    HLD hld(edges);
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 2) {
            int u, v;
            cin >> u >> v;
            u--; // 0-indexed
            v--; // 0-indexed
            cout << hld.query(u, v) << '\n';
        } else {
            int idx;
            ll value;
            cin >> idx >> value;
            idx--; // 0-indexed
            hld.update(idx, value);
        }
    }

    return 0;
}