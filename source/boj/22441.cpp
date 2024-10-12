// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll lcm(ll a, ll b) {
    return a / __gcd(a, b) * b;
}

struct SegTree {
    int n;
    vector<ll> tree;

    SegTree(int n) : n(n), tree(n * 4) {}
    SegTree(vector<ll> &v) : n(v.size()), tree(v.size() * 4) {
        init(v, 1, 0, n - 1);
    }

    ll init(vector<ll> &v, int node, int left, int right) {
        if (left == right) {
            return tree[node] = v[left];
        }

        int mid = (left + right) / 2;
        return tree[node] = lcm(init(v, node * 2, left, mid), init(v, node * 2 + 1, mid + 1, right));
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    ll query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) {
            return 1;
        }

        if (l <= s && e <= r) {
            return tree[node];
        }

        int mid = (s + e) / 2;
        return lcm(query(node * 2, s, mid, l, r), query(node * 2 + 1, mid + 1, e, l, r));
    }
};

ll modpow(ll a, ll b, ll mod) {
    ll ret = 1;
    while (b) {
        if (b % 2) {
            ret = ret * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }

    return ret;
}

ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    vector<vector<ll>> cycle;
    vector<ll> cycle_no(n + 1, -1);
    vector<ll> cycle_sum;

    for (int i = 0; i < n; i++) {
        if (cycle_no[i] != -1) {
            continue;
        }

        ll cur = i;
        cycle.push_back({});
        cycle_sum.push_back(0);
        ll sum = 0;
        while (cycle_no[cur] == -1) {
            cycle_no[cur] = cycle.size() - 1;
            cycle.back().push_back(cur);
            sum += v[cur];
            cur = v[cur];
        }
        cycle_sum.back() = sum;
    }

    vector<ll> cycle_size_by_index(n + 1);
    for (int i = 0; i < cycle.size(); i++) {
        for (int j = 0; j < cycle[i].size(); j++) {
            cycle_size_by_index[cycle[i][j]] = cycle[i].size();
        }
    }

    ll lcm_whole = 1;
    for (int i = 0; i < cycle.size(); i++) {
        lcm_whole = lcm_whole / __gcd(lcm_whole, (ll)cycle[i].size()) * cycle[i].size();
    }

    SegTree st(cycle_size_by_index);
    vector<ll> prefix_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = (prefix_sum[i - 1] + cycle_sum[cycle_no[i]] * (lcm_whole / cycle_size_by_index[i] % MOD1)) % MOD1;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        ll ret = (prefix_sum[r] - prefix_sum[l - 1] + 3 * MOD1) % MOD1;
        ll cycle_lcm = st.query(l, r);
        ret *= modinv(lcm_whole / cycle_lcm % MOD1, MOD1);
        ret %= MOD1;
        cout << ret << '\n';
    }

    return 0;
}