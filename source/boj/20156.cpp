#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Query {
    int id, turn, u, v;
    Query() {
        id = 0;
        turn = 0;
        u = 0;
        v = 0;
    }
    Query(int _id, int _turn, int _u, int _v) : id(_id), turn(_turn), u(_u), v(_v) {}
};

struct Dsu {
    int n;
    vector<int> roots, sizes;
    Dsu(int n) {
        this->n = n;
        roots.resize(n);
        sizes.resize(n, 1);
        iota(roots.begin(), roots.end(), 0);
    }

    int find(int u) {
        if (roots[u] == u) {
            return u;
        }
        return roots[u] = find(roots[u]);
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    int get_size(int u) {
        u = find(u);
        return sizes[u];
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return;
        }
        if (get_size(u) < get_size(v)) {
            swap(u, v);
        }
        sizes[u] += sizes[v];
        roots[v] = u;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> parents(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> parents[i];
    }

    vector<pii> events(m);
    for (int i = 0; i < m; i++) {
        int u;
        cin >> u;
        if (parents[u] != -1) {
            events[i] = {u, parents[u]};
            parents[u] = -1;
        } else {
            events[i].first = events[i].second = -1;
        }
    }

    vector<Query> queries(k);
    vector<bool> ans(k);
    for (int i = 0; i < k; i++) {
        int turn, u, v;
        cin >> turn >> u >> v;
        queries[i] = {i, turn, u, v};
    }
    sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b) { return a.turn > b.turn; });

    Dsu dsu(n + 1);
    for (int i = 1; i <= n; i++) {
        if (parents[i] != -1) {
            dsu.merge(i, parents[i]);
        }
    }

    auto iter = queries.begin();
    for (int i = m - 1; i >= 0; i--) {
        while (!(iter == queries.end()) && iter->turn > i) {
            ans[iter->id] = dsu.same(iter->u, iter->v);
            iter++;
        }
        if (events[i].first != -1) {
            dsu.merge(events[i].first, events[i].second);
        }
    }

    while (!(iter == queries.end())) {
        ans[iter->id] = dsu.same(iter->u, iter->v);
        iter++;
    }

    for (int i = 0; i < k; i++) {
        cout << (ans[i] ? "Same Same;" : "No;") << '\n';
    }

    return 0;
}