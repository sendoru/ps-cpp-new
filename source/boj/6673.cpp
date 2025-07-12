// #include "atcoder/aint"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MOD9 = 998244353;
const int MOD1 = (int)1e9 + 7;

vector<vector<int>> mat_mul(const vector<vector<int>> &a, const vector<vector<int>> &b, int mod) {
    int n = a.size(), m = b[0].size(), k = a[0].size();
    vector<vector<int>> c(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int l = 0; l < k; l++) {
                c[i][j] = (c[i][j] + a[i][l] * b[l][j]) % mod;
            }
        }
    }
    return c;
}

vector<vector<int>> mat_pow(const vector<vector<int>> &a, int p, int mod) {
    int n = a.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    vector<vector<int>> base = a;
    while (p) {
        if (p & 1) {
            res = mat_mul(res, base, mod);
        }
        base = mat_mul(base, base, mod);
        p >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        int k;
        cin >> k;
        if (k == 0) {
            break;
        }

        vector<int> a(k), b(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < k; i++) {
            cin >> b[i];
        }
        int n;
        cin >> n;

        vector<vector<int>> mat(k, vector<int>(k, 0));
        for (int i = 0; i < k - 1; i++) {
            mat[i][i + 1] = 1;
        }
        for (int i = 0, j = k - 1; i < k; i++, j--) {
            mat.back()[i] = b[j];
        }

        vector<vector<int>> powered = mat_pow(mat, n, 10000);
        vector<vector<int>> a_2d(k, vector<int>(1, 0));
        for (int i = 0; i < k; i++) {
            a_2d[i][0] = a[i];
        }
        int ans = mat_mul(powered, a_2d, 10000)[0][0];
        cout << ans << "\n";
    }

    return 0;
}