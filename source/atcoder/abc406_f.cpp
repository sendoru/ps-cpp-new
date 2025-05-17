// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// from atcoder library
template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S> &v) : _n(int(v.size()))
    {
        log = ceil(log2(_n));
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x)
    {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p) const
    {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const
    {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)>
    int max_right(int l) const
    {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>
    int max_right(int l, F f) const
    {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n)
            return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0)
                l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)>
    int min_left(int r) const
    {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F>
    int min_left(int r, F f) const
    {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0)
            return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

ll intSum(ll a, ll b) { return a + b; }
ll zero() { return 0ll; }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<vector<int>> adj_list(n);
    vector<pii> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
        edges.push_back({u, v});
    }

    // prepare for euler tour
    vector<int> levels(n, -1), order;
    vector<vector<int>> pos(n);
    function<void(int, int)> dfs = [&](int cur, int level) {
        levels[cur] = level;
        // start of the tour
        pos[cur].push_back(order.size());
        order.push_back(cur);
        for (int next : adj_list[cur]) {
            if (levels[next] == -1) {
                dfs(next, level + 1);
            }
        }
        // end of the tour
        pos[cur].push_back(order.size());
        order.push_back(cur);
    };

    dfs(0, 0);
    // make sure second is child
    for (auto &edge : edges) {
        if (levels[edge.first] > levels[edge.second]) {
            swap(edge.first, edge.second);
        }
    }
    vector<ll> seg_base(order.size(), 1);
    segtree<ll, intSum, zero> seg(seg_base);
    ll weight_sum = n;

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        // 1, increase weight
        if (t == 1) {
            ll node, w;
            cin >> node >> w;
            node--;
            weight_sum += w;
            seg.set(pos[node][0], seg.get(pos[node][0]) + w);
            seg.set(pos[node][1], seg.get(pos[node][1]) + w);
        }
        // 2. query weight
        else if (t == 2) {
            ll edge;
            cin >> edge;
            edge--;
            ll child = edges[edge].second;
            ll subtree_sum = seg.prod(pos[child][0], pos[child][1] + 1) / 2;
            ll remain_sum = weight_sum - subtree_sum;
            cout << abs(subtree_sum - remain_sum) << '\n';
        }
    }

    return 0;
}