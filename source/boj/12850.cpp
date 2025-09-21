// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

template <size_t N>
array<array<ll, N>, N> mat_mul(const array<array<ll, N>, N> &a, const array<array<ll, N>, N> &b, ll mod) {
    array<array<ll, N>, N> c{};
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            for (size_t k = 0; k < N; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return c;
}

template <size_t N>
array<array<ll, N>, N> mat_pow(array<array<ll, N>, N> a, ll p, ll mod) {
    array<array<ll, N>, N> res{};
    for (size_t i = 0; i < N; i++) {
        res[i][i] = 1;
    }
    while (p) {
        if (p & 1) {
            res = mat_mul<N>(res, a, mod);
        }
        a = mat_mul<N>(a, a, mod);
        p >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    array<array<ll, 8>, 8> A = {};
    vector<pii> edges = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {2, 4}, {3, 4}, {3, 5}, {4, 5}, {4, 6}, {5, 7}, {6, 7}};
    for (auto [u, v] : edges) {
        A[u][v]++;
        A[v][u]++;
    }

    ll n;
    cin >> n;
    auto ans = mat_pow<8>(A, n, MOD1);
    cout << ans[0][0] << "\n";

    return 0;
}