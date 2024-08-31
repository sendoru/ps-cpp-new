#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<ll>> matmul(vector<vector<ll>> &a, vector<vector<ll>> &b, ll mod) {
    int n = a.size();
    int m = b.size();
    int l = b[0].size();
    assert(a[0].size() == m);
    vector<vector<ll>> ret(n, vector<ll>(l));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            for (int k = 0; k < m; k++) {
                ret[i][j] += a[i][k] * b[k][j];
                ret[i][j] %= mod;
            }
        }
    }

    return ret;
}

vector<ll> linear_transform(vector<vector<ll>> &a, vector<ll> &b) {
    int n = a.size();
    int m = b.size();
    assert(a[0].size() == m);
    vector<ll> ret(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ret[i] += a[i][j] * b[j];
        }
    }

    return ret;
}

vector<vector<ll>> id(int n) {
    vector<vector<ll>> ret(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        ret[i][i] = 1;
    }

    return ret;
}

vector<vector<ll>> matpow(vector<vector<ll>> &base, ll exp, ll mod) {
    auto cur = id(base.size());
    for (; exp; exp >>= 1) {
        if (exp & 1) {
            cur = matmul(cur, base, mod);
        }
        base = matmul(base, base, mod);
    }

    return cur;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll k, n;
    cin >> k >> n;
    vector<vector<ll>> A(k + 1, vector<ll>(k + 1));
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            if (__gcd(i, j) == 1) {
                A[i][j] = 1;
            }
        }
    }

    auto A_pow = matpow(A, n - 1, MOD1);
    auto x1 = vector<ll>(k + 1, 1);
    x1[0] = 0;
    auto ans = linear_transform(A_pow, x1);
    cout << accumulate(ans.begin(), ans.end(), 0LL) % MOD1 << "\n";

    return 0;
}