#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<double> cpx;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll base, ll exp, ll mod) {
    ll ret = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            ret = ret * base % mod;
        }
        base = base * base % mod;
        exp /= 2;
    }
    return ret;
}

void ntt(vector<ll> &v, bool inv) {
    int n = v.size();
    int log2n = (int)(round(log2(n)));
    for (int i = 1; i < n; i++) {
        int j = 0;
        for (int k = 0; k < log2n; k++) {
            j <<= 1;
            j |= (i >> k) & 1;
        }
        if (i < j) {
            swap(v[i], v[j]);
        }
    }

    vector<ll> roots(n);
    ll x = modpow(3, (MOD9 - 1) / n, MOD9);
    if (inv) {
        x = modpow(x, MOD9 - 2, MOD9);
    }
    roots[0] = 1;
    for (int i = 1; i < n; i++) {
        roots[i] = roots[i - 1] * x % MOD9;
    }

    for (int ang_idx = 0, bucket_size = 2; bucket_size <= n; bucket_size <<= 1, ang_idx++) {
        ll ang = roots[n / bucket_size];
        for (int i = 0; i < n; i += bucket_size) {
            ll wk = 1;
            for (int j = 0; j < bucket_size / 2; j++) {
                ll x = v[i + j];
                ll y = v[i + j + bucket_size / 2] * wk % MOD9;
                v[i + j] = (x + y) % MOD9;
                v[i + j + bucket_size / 2] = (x - y + MOD9) % MOD9;
                wk = wk * ang % MOD9;
            }
        }
    }
    if (inv) {
        ll n_inv = modpow(n, MOD9 - 2, MOD9);
        for (int i = 0; i < n; i++) {
            v[i] = v[i] * n_inv % MOD9;
        }
    }
}

void convolve(vector<ll> &v1, vector<ll> &v2) {
    int n = 1;
    while (n < v1.size() + v2.size()) {
        n <<= 1;
    }
    v1.resize(n);
    v2.resize(n);
    ntt(v1, false);
    ntt(v2, false);
    for (int i = 0; i < n; i++) {
        v1[i] = v1[i] * v2[i] % MOD9;
    }
    ntt(v1, true);
}

vector<bool> eratos(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    auto is_prime = eratos(1000000);

    vector<ll> v1(500'001), v2(500'001);
    for (int i = 1, j = 0; i <= 1000000; i += 2, j++) {
        v1[j] = is_prime[i];
        v2[j] = is_prime[i];
    }
    convolve(v1, v2);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 4) {
            cout << 1 << "\n";
            continue;
        }
        cout << (v1[(n - 1) / 2] + 1) / 2 << "\n";
    }

    return 0;
}