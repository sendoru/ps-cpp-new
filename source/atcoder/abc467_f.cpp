#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Node {
    ll a_sum;
    ll opt;
};

Node merge_node(const Node &l, const Node &r) {
    return Node{l.a_sum + r.a_sum, max(r.opt, r.a_sum + l.opt)};
}

Node e() {
    return {0, 0};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<array<ll, 3>> queries(q);
    for (int i = 0; i < q; i++) {
        ll t, idx, x;
        cin >> t >> idx >> x;
        idx--;
        queries[i] = {t, idx, x};
    }

    vector<ll> unique_b_vals = b;
    for (int i = 0; i < q; i++) {
        if (queries[i][0] == 2) {
            unique_b_vals.push_back(queries[i][2]);
        }
    }

    sort(unique_b_vals.begin(), unique_b_vals.end());
    unique_b_vals.erase(unique(unique_b_vals.begin(), unique_b_vals.end()), unique_b_vals.end());
    vector<ll> b_comp = b;
    for (int i = 0; i < n; i++) {
        b_comp[i] = lower_bound(unique_b_vals.begin(), unique_b_vals.end(), b[i]) - unique_b_vals.begin();
    }

    map<ll, ll> b_val_to_idx;
    for (int i = 0; i < unique_b_vals.size(); i++) {
        b_val_to_idx[unique_b_vals[i]] = i;
    }

    ll b_cnt = unique_b_vals.size();
    atcoder::segtree<Node, merge_node, e> seg(b_cnt);
    for (int i = 0; i < n; i++) {
        auto node = seg.get(b_comp[i]);
        node.a_sum += a[i];
        if (node.opt == 0) {
            node.opt = a[i] + b[i];
        } else {
            node.opt += a[i];
        }
        seg.set(b_comp[i], node);
    }

    for (int i = 0; i < q; i++) {
        int qt = queries[i][0];
        int idx = queries[i][1];
        ll x = queries[i][2];

        if (qt == 1) {
            // change a[idx] to x
            ll old_a = a[idx];
            a[idx] = x;
            auto node = seg.get(b_comp[idx]);
            node.a_sum += (x - old_a);
            node.opt += (x - old_a);
            seg.set(b_comp[idx], node);
        } else {
            // change b[idx] to x
            ll old_b = b[idx];
            b[idx] = x;
            ll old_b_idx = b_val_to_idx[old_b];
            ll new_b_idx = b_val_to_idx[x];
            b_comp[idx] = new_b_idx;

            auto old_node = seg.get(old_b_idx);
            old_node.a_sum -= a[idx];
            if (old_node.a_sum == 0) {
                old_node.opt = 0;
            } else {
                old_node.opt -= a[idx];
            }
            seg.set(old_b_idx, old_node);

            auto new_node = seg.get(new_b_idx);
            new_node.a_sum += a[idx];
            if (new_node.opt == 0) {
                new_node.opt = a[idx] + x;
            } else {
                new_node.opt += a[idx];
            }
            seg.set(new_b_idx, new_node);
        }

        auto res = seg.all_prod();
        cout << res.opt << '\n';
    }

    return 0;
}