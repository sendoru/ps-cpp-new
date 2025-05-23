// #include "atcoder/all"
#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll MAX = 2e5 + 5;

ll modpow_p_cache[MAX], modpow_q_cache[MAX];
ll p, q;

ll modpow(ll a, ll b, ll mod) {
    if (a == p) {
        return modpow_p_cache[b];
    }
    if (a == q) {
        return modpow_q_cache[b];
    }
    ll res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

// from atcoder library (CC0 License)
template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size())) {
        log = ceil(log2(_n));
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }

        S sml = e(), smr = e();
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

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1)
                    all_apply(l++, f);
                if (r & 1)
                    all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l)
                update(l >> i);
            if (((r >> i) << i) != r)
                update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)>
    int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n)
            return _n;
        l += size;
        for (int i = log; i >= 1; i--)
            push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0)
                l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
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

    template <bool (*g)(S)>
    int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0)
            return 0;
        r += size;
        for (int i = log; i >= 1; i--)
            push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
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
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size)
            lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

struct S {
    ll val, size;
};

struct F {
    ll a, b;
    F() {
        a = 1;
        b = 0;
    }
    F(ll a, ll b) : a(a), b(b) {}
};

S op(S x, S y) {
    return {(x.val + y.val) % MOD9, x.size + y.size};
}

S e() {
    return {0, 0};
}

S mapping(F f, S x) {
    return {(x.val * f.a + x.size * f.b) % MOD9, x.size};
};

F id() {
    return F();
}

F compose(F f, F g) {
    return {f.a * g.a % MOD9, (f.a * g.b + f.b) % MOD9};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    cin >> p >> q;
    modpow_p_cache[0] = 1;
    modpow_q_cache[0] = 1;
    for (int i = 1; i < MAX; i++) {
        modpow_p_cache[i] = modpow_p_cache[i - 1] * p % MOD9;
        modpow_q_cache[i] = modpow_q_cache[i - 1] * q % MOD9;
    }
    vector<pll> ab(n);
    for (int i = 0; i < n; i++) {
        cin >> ab[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> ab[i].second;
    }
    sort(ab.begin(), ab.end());
    vector<S> seg_base(MAX, S{0, 1});
    lazy_segtree<S, op, e, F, mapping, compose, id> st1(seg_base), st2(seg_base);
    st1.apply(0, F(1, 1));
    st2.apply(0, F(1, 1));
    ll ans = 1;

    for (int i = 0; i < n; i++) {
        ll a = ab[i].first;
        ll b = ab[i].second;
        ll cur = modpow(p, a, MOD9) * st1.prod(0, b).val % MOD9 * modpow(q, b, MOD9) % MOD9;
        cur += modpow(p, a, MOD9) * st2.prod(b, MAX).val % MOD9;
        cur %= MOD9;
        ans = (ans + cur) % MOD9;
        // idx = b 이상 구간에 2배
        st1.apply(b, MAX, F(2, 0));
        st2.apply(b, MAX, F(2, 0));
        // idx = b에 query1(0, b - 1) 더하기
        st1.apply(b, F(1, st1.prod(0, b).val));
        st2.apply(b, F(1, st1.prod(0, b).val * modpow(q, b, MOD9) % MOD9));
        // cout << st.query1(0, MAX - 1) << '\n';
    }

    cout << ans * modinv(modpow(2, n, MOD9), MOD9) % MOD9 << '\n';

    return 0;
}