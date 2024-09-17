// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll get_cost_naive(vector<ll> v) {
    ll ret = 0;
    while (true) {
        bool sorted = true;
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i] > v[i + 1]) {
                sorted = false;
                swap(v[i], v[i + 1]);
                ret += abs(v[i] - v[i + 1]);
            }
        }
        if (sorted) {
            break;
        }
    }

    return ret;
}

ll get_cost_rev(vector<ll> v) {
    ll ret = 0;
    while (true) {
        bool sorted = true;
        for (int i = v.size() - 2; i >= 0; i--) {
            if (v[i] > v[i + 1]) {
                sorted = false;
                swap(v[i], v[i + 1]);
                ret += abs(v[i] - v[i + 1]);
            }
        }
        if (sorted) {
            break;
        }
    }

    return ret;
}

ll get_cost_rand(vector<ll> v) {
    ll ret = 0;
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> dist(0, v.size() - 2);
    for (int i = 0; i < 200; i++) {
        int idx = dist(g);
        if (v[idx] > v[idx + 1]) {
            swap(v[idx], v[idx + 1]);
            ret += abs(v[idx] - v[idx + 1]);
        }
    }

    while (true) {
        bool sorted = true;
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i] > v[i + 1]) {
                sorted = false;
                swap(v[i], v[i + 1]);
                ret += abs(v[i] - v[i + 1]);
            }
        }
        if (sorted) {
            break;
        }
    }

    return ret;
}

struct SegTree {
    int n;
    vector<ll> tree;
    SegTree(int _n) {
        n = 1;
        while (n < _n)
            n <<= 1;
        tree.resize(n << 1);
    }
    void update(int idx, ll val) {
        idx += n;
        tree[idx] = val;
        for (idx >>= 1; idx > 0; idx >>= 1) {
            tree[idx] = (tree[idx << 1] + tree[idx << 1 | 1]) % MOD1;
        }
    }
    ll prod(int l, int r) {
        l = max(l, 0);
        r = min(r, (int)n + 1);
        ll ret = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = (ret + tree[l++]) % MOD1;
            if (r & 1)
                ret = (ret + tree[--r]) % MOD1;
        }
        return ret;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // random permutation
    // for (int i = 0; i < 20; i++) {
    //     vector<ll> v(30);
    //     iota(v.begin(), v.end(), 0);
    //     random_device rd;
    //     mt19937 g(rd());
    //     shuffle(v.begin(), v.end(), g);
    //     ll forward_cost = get_cost_naive(v);
    //     ll backward_cost = get_cost_rev(v);
    //     ll random_cost = get_cost_rand(v);
    //     cout << "forward: " << get_cost_naive(v) << ", backward: " << get_cost_rev(v) << ", random: " << get_cost_rand(v) << '\n';
    //     if (forward_cost != backward_cost || forward_cost != random_cost) {
    //         cout << "The cost is different\n";
    //     }
    // }

    int t;
#ifdef DEBUG
    t = 30;
#else
    t = 1;
#endif
    while (t--) {
        ll n;
#ifdef DEBUG
        n = 100;
#else
        cin >> n;
#endif
        vector<ll> v(n);
#ifdef DEBUG
        iota(v.begin(), v.end(), 1);
        random_device rd;
        mt19937 g(rd());
        shuffle(v.begin(), v.end(), g);
#else
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
#endif

        SegTree st1(n + 1), stv(n + 1);
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            stv.update(v[i], v[i]);
            st1.update(v[i], 1);

            ll stv_prod = stv.prod(v[i] + 1, n + 1);
            ll st1_prod = st1.prod(v[i] + 1, n + 1);
            ans += stv_prod - st1_prod * v[i];
            ans = (ans % MOD1 + MOD1) % MOD1;
        }

        cout << ans << ' ';
#ifdef DEBUG
        cout << "Naive: " << get_cost_naive(v) << '\n';
        if (ans != get_cost_naive(v)) {
            cout << "The cost is different\n";
        }
#endif
    }

    return 0;
}