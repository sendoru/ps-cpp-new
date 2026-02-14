// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> small_primes;

// up to sqrt n is enough for factorization
void preprocess_primes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            small_primes.push_back(i);
            for (int j = i * 2; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

pair<vector<int>, int> factorize(ll x) {
    vector<int> res(small_primes.size());
    for (int i = 0; i < small_primes.size() && (ll)small_primes[i] * small_primes[i] <= x; i++) {
        while (x % small_primes[i] == 0) {
            x /= small_primes[i];
            res[i]++;
        }
    }
    if (x > 1 && x <= small_primes.back()) {
        auto it = lower_bound(small_primes.begin(), small_primes.end(), x);
        if (it != small_primes.end() && *it == x) {
            res[it - small_primes.begin()]++;
            return {res, 1};
        }
    } else if (x > 1) {
        return {res, x};
    }
    return {res, 1};
}

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

struct SegTree {
    int n;
    vector<array<char, 600>> tree;

    SegTree(const vector<array<char, 600>> &data) {
        n = 1;
        while (n < data.size()) {
            n *= 2;
        }
        tree.resize(2 * n);
        for (int i = 0; i < data.size(); i++) {
            tree[n + i] = data[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i] = tree[2 * i];
            for (int j = 0; j < 600; j++) {
                tree[i][j] = max(tree[i][j], tree[2 * i + 1][j]);
            }
        }
    }

    array<char, 600> query(int l, int r) {
        array<char, 600> res{};
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                for (int i = 0; i < 600; i++) {
                    res[i] = max(res[i], tree[l][i]);
                }
                l++;
            }
            if (r & 1) {
                r--;
                for (int i = 0; i < 600; i++) {
                    res[i] = max(res[i], tree[r][i]);
                }
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    preprocess_primes(sqrt(1e7) + 10);

    ll T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<array<char, 600>> f(2 * n);
        vector<ll> large_primes(2 * n, 1);
        for (int i = 0; i < n; i++) {
            auto [factor_cnt, large_prime] = factorize(a[i]);
            // process large primes separately
            large_primes[i] = large_prime;
            large_primes[n + i] = large_prime;
            for (int j = 0; j < factor_cnt.size(); j++) {
                f[i][j] = factor_cnt[j];
                f[n + i][j] = factor_cnt[j];
            }
        }

        SegTree seg(f);
        ll large_prime_prod = 1;
        unordered_map<ll, ll> cur_large_primes;
        for (int i = 1; i < n; i++) {
            if (large_primes[i] > 1) {
                if (cur_large_primes[large_primes[i]] == 0) {
                    large_prime_prod = large_prime_prod * large_primes[i] % MOD9;
                }
                cur_large_primes[large_primes[i]]++;
            }
        }

        for (int i = 1; i <= n; i++) {
            auto res = seg.query(i, n + i - 1);
            ll ans = 1;
            for (int j = 0; j < res.size(); j++) {
                if (res[j] > 0) {
                    ans = ans * modpow(small_primes[j], res[j], MOD9) % MOD9;
                }
            }
            ans = ans * large_prime_prod % MOD9;
            cout << ans << ' ';

            if (large_primes[i] != 1 && cur_large_primes[large_primes[i]] == 1) {
                large_prime_prod = large_prime_prod * modpow(large_primes[i], MOD9 - 2, MOD9) % MOD9;
            }
            cur_large_primes[large_primes[i]]--;

            if (large_primes[n + i - 1] != 1 && cur_large_primes[large_primes[n + i - 1]] == 0) {
                large_prime_prod = large_prime_prod * large_primes[n + i - 1] % MOD9;
            }
            cur_large_primes[large_primes[n + i - 1]]++;
        }
        cout << '\n';
    }

    return 0;
}