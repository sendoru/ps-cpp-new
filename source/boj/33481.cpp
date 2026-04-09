// #include "atcoder/all"
// #define DEBUG
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

template <ll mod>
struct ModInt {
    ll val;
    ModInt() : val(0) {}
    ModInt(ll v) : val(v % mod) {
        if (val < 0)
            val += mod;
    }

    ModInt operator+(const ModInt &other) const {
        return ModInt(val + other.val);
    }
    ModInt operator-(const ModInt &other) const {
        return ModInt(val - other.val);
    }
    ModInt operator*(const ModInt &other) const {
        return ModInt(val * other.val);
    }
    ModInt operator/(const ModInt &other) const {
        return *this * other.inv();
    }
    ModInt pow(ll e) const {
        ModInt res(1), base(val);
        while (e) {
            if (e & 1)
                res = res * base;
            base = base * base;
            e >>= 1;
        }
        return res;
    }
    ModInt inv() const {
        return pow(mod - 2);
    }
    ModInt &operator+=(const ModInt &other) {
        val = (other.val + val) % mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &other) {
        val = (val - other.val + mod) % mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &other) {
        val = val * other.val % mod;
        return *this;
    }
    ModInt &operator/=(const ModInt &other) {
        return *this *= other.inv();
    }
};

ll modpow(ll b, ll e, ll m) {
    b %= m;
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

ll sum_naive(vector<ll> &a, ll m) {
    ll n = a.size() - 1;
    ll denom = 3 * n * (n - 1) / 2 + n;
    ll sum_orig = accumulate(a.begin() + 1, a.end(), 0LL) % MOD1;
    ll sum_expect = 0;
    function<void(int, vector<ll>)> dfs = [&](int idx, vector<ll> cur) {
        if (idx == m) {
            ll sum_cur = accumulate(cur.begin() + 1, cur.end(), 0LL) % MOD1;
            sum_expect = sum_expect + sum_cur;
            sum_expect %= MOD1;
            return;
        }
        for (ll i = 1; i <= n; i++) {
            vector<ll> nxt = cur;
            nxt[i] = nxt[i] * i % MOD1;
            dfs(idx + 1, nxt);
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 1; r <= n; r++) {
                vector<ll> nxt = cur;
                for (int i = l; i <= r; i++) {
                    nxt[i] = cur[i] * i % MOD1;
                }
                dfs(idx + 1, nxt);
                for (int i = l; i <= r; i++) {
                    nxt[i] = cur[i] * l % MOD1;
                }
                dfs(idx + 1, nxt);
                for (int i = l; i <= r; i++) {
                    nxt[i] = cur[i] * r % MOD1;
                }
                dfs(idx + 1, nxt);
            }
        }
    };

    dfs(0, a);
    return sum_expect * modinv(sum_orig, MOD1) % MOD1 * modinv(modpow(denom, m, MOD1), MOD1) % MOD1;
}

ll prod_naive(vector<ll> &a, ll m) {
    ll n = a.size() - 1;
    ll denom = 3 * n * (n - 1) / 2 + n;
    ll prod_orig = 1;
    for (int i = 1; i <= n; i++) {
        prod_orig = prod_orig * a[i] % MOD1;
    }
    ll prod_expect = 0;
    function<void(int, vector<ll>)> dfs = [&](int idx, vector<ll> cur) {
        if (idx == m) {
            ll prod_cur = 1;
            for (int i = 1; i <= n; i++) {
                prod_cur = prod_cur * cur[i] % MOD1;
            }
            prod_expect = prod_expect + prod_cur;
            prod_expect %= MOD1;
            return;
        }
        for (ll i = 1; i <= n; i++) {
            vector<ll> nxt = cur;
            nxt[i] = nxt[i] * i % MOD1;
            dfs(idx + 1, nxt);
        }
        for (int l = 1; l <= n; l++) {
            for (int r = l + 1; r <= n; r++) {
                vector<ll> nxt = cur;
                for (int i = l; i <= r; i++) {
                    nxt[i] = cur[i] * i % MOD1;
                }
                dfs(idx + 1, nxt);
                for (int i = l; i <= r; i++) {
                    nxt[i] = cur[i] * l % MOD1;
                }
                dfs(idx + 1, nxt);
                for (int i = l; i <= r; i++) {
                    nxt[i] = cur[i] * r % MOD1;
                }
                dfs(idx + 1, nxt);
            }
        }
    };

    dfs(0, a);
    return prod_expect * modinv(prod_orig, MOD1) % MOD1 * modinv(modpow(denom, m, MOD1), MOD1) % MOD1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll denom = 3 * n * (n - 1) / 2 + n;
    ll denom_inv = modinv(denom, MOD1);
    ll two_inv = modinv(2, MOD1);

    char qt;
    cin >> qt;
    if (qt == 'S') {
        vector<ll> expect(n + 1);
        for (ll i = 1; i <= n; i++) {
            // q1
            ll cur_expect = i;

            // q2
            cur_expect += i * i % MOD1 * (n - i + 1) % MOD1 + MOD1 - i;
            cur_expect = cur_expect % MOD1;

            // q3
            cur_expect += i * (i + 1) / 2 % MOD1 * (n - i + 1) % MOD1 + MOD1 - i;
            cur_expect = cur_expect % MOD1;

            // q4
            cur_expect += (n * (n + 1) / 2 - i * (i - 1) / 2) % MOD1 * i % MOD1 + MOD1 - i;
            cur_expect = cur_expect % MOD1;

            // not included in any queries
            cur_expect += denom - 3 * (i * (n - i + 1) - 1) - 1;
            cur_expect = (cur_expect % MOD1 + MOD1) % MOD1;

            expect[i] = cur_expect * denom_inv % MOD1;
        }

        ll orig_sum = 0;
        for (ll i = 1; i <= n; i++) {
            orig_sum = (orig_sum + a[i]) % MOD1;
        }

        ll expect_sum = 0;
        for (ll i = 1; i <= n; i++) {
            expect_sum = (expect_sum + a[i] * modpow(expect[i], m, MOD1)) % MOD1;
        }

        ll ans = expect_sum * modinv(orig_sum, MOD1) % MOD1;
#ifdef DEBUG
        ll ans_naive = sum_naive(a, m);
        assert(ans == ans_naive);
#endif
        cout << ans << "\n";
    }

    else {
        ModInt<MOD1> expect_ratio = 0;

        // q1
        for (ll i = 1; i <= n; i++) {
            expect_ratio += i;
        }

        // q2
        vector<ll> facts(n + 1);
        facts[0] = 1;
        for (ll i = 1; i <= n; i++) {
            facts[i] = facts[i - 1] * i % MOD1;
        }
        vector<ll> fact_pf_sum(n + 1);
        fact_pf_sum[0] = 1;
        for (ll i = 1; i <= n; i++) {
            fact_pf_sum[i] = (fact_pf_sum[i - 1] + facts[i]) % MOD1;
        }
        for (ll i = 1; i <= n; i++) {
            expect_ratio += (fact_pf_sum.back() - fact_pf_sum[i - 1] + MOD1) * modinv(facts[i - 1], MOD1) % MOD1;
            expect_ratio -= i;
        }

        // q3
        expect_ratio += n - 1;
        for (ll i = 2; i <= n; i++) {
            expect_ratio += (ModInt<MOD1>(i).pow(n - i + 1) - 1) * i * modinv(i - 1, MOD1) - i;
        }

        // q4
        for (ll i = 2; i <= n; i++) {
            expect_ratio += (ModInt<MOD1>(i).pow(i) - 1) * i * modinv(i - 1, MOD1) - i;
        }

        ll ans = modpow(expect_ratio.val * denom_inv % MOD1, m, MOD1);
#ifdef DEBUG
        ll ratio_naive = prod_naive(a, m);
        assert(ans == ratio_naive);
#endif
        cout << ans << "\n";
    }

    return 0;
}

/*
10 3
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
*/