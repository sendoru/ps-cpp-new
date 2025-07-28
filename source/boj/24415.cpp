// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

template <typename T>
vector<vector<T>> matmul(const vector<vector<T>> &a, const vector<vector<T>> &b, T mod) {
    int n = a.size(), m = b[0].size(), k = a[0].size();
    vector<vector<T>> res(n, vector<T>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int l = 0; l < k; l++) {
                res[i][j] = (res[i][j] + a[i][l] * b[l][j]) % mod;
            }
        }
    }
    return res;
}

template <typename T>
vector<T> linear(const vector<vector<T>> &a, const vector<T> &b, T mod) {
    int n = a.size(), m = a[0].size();
    vector<T> res(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i] = (res[i] + a[i][j] * b[j]) % mod;
        }
    }
    return res;
}

template <typename T>
vector<vector<T>> matpow(const vector<vector<T>> &a, ll e, T mod) {
    int n = a.size();
    vector<vector<T>> res(n, vector<T>(n, 0));
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    vector<vector<T>> base = a;

    while (e) {
        if (e & 1)
            res = matmul(res, base, mod);
        base = matmul(base, base, mod);
        e >>= 1;
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, c, k;
    cin >> n >> c >> k;
    string s;
    cin >> s;
    vector<tuple<char, ll, ll>> moves(c);
    for (int i = 0; i < c; i++) {
        char ch;
        ll l, r;
        cin >> ch >> l >> r;
        moves[i] = {ch, l, r};
    }
    vector<int> hv(n + 1);
    for (int i = 0; i < n; i++) {
        hv[i] = s[i] - 'A';
    }
    hv[n] = 1;
    vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        mat[i][i] = 1;
    }
    for (const auto &[ch, i, j] : moves) {
        if (ch == 'S') {
            swap(mat[i], mat[j]);
        } else {
            mat[i][n] = (mat[i][n] + j) % 26;
        }
    }

    ll d = k / c;
    ll r = k % c;
    vector<vector<int>> mat1 = matpow(mat, d, 26);
    vector<int> hv1 = linear(mat1, hv, 26);
    for (int i = 0; i < r; i++) {
        const auto &[ch, l, r] = moves[i];
        if (ch == 'S') {
            swap(hv1[l], hv1[r]);
        } else {
            hv1[l] = (hv1[l] + r) % 26;
        }
    }

    string ans(n, 'A');
    for (int i = 0; i < n; i++) {
        ans[i] = 'A' + hv1[i];
    }
    cout << ans << '\n';

    return 0;
}