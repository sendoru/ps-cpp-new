// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

vector<ll> solve_lineq_on_zp(vector<vector<ll>> &A, vector<ll> &b, ll p) {
    int n = A.size();
    int m = A[0].size();
    assert(b.size() == n);
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++) {
            if (A[i][col] != 0) {
                sel = i;
                break;
            }
        }
        if (A[sel][col] == 0) {
            continue;
        }
        swap(A[sel], A[row]);
        swap(b[sel], b[row]);
        where[col] = row;
        
        // make first none-zero element 1
        ll inv = modinv(A[row][col], p);
        for (int i = col; i < m; i++) {
            A[row][i] = (A[row][i] * inv) % p;
        }
        b[row] = (b[row] * inv) % p;

        // eliminate other rows
        for (int i = 0; i < n; i++) {
            if (i != row) {
                ll factor = A[i][col];
                for (int j = col; j < m; j++) {
                    A[i][j] = (A[i][j] - factor * A[row][j] % p + p) % p;
                }
                b[i] = (b[i] - factor * b[row] % p + p) % p;
            }
        }
        row++;
    }

    vector<ll> ans(m, 0);
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) {
            ans[i] = b[where[i]];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll p;
        cin >> p;
        string s;
        cin >> s;
        int n = s.size();
        vector<ll> b(s.size());
        for (int i = 0; i < n; i++) {
            if (s[i] == '*') {
                b[i] = 0;
            } else {
                b[i] = s[i] - 'a' + 1;
            }
        }

        vector<vector<ll>> A(n, vector<ll>(n));
        for (int i = 0; i < n; i++) {
            A[i][0] = 1;
            for (int j = 1; j < n; j++) {
                A[i][j] = (A[i][j - 1] * (i + 1)) % p;
            }
        }

        auto res = solve_lineq_on_zp(A, b, p);
        for (int i = 0; i < n; i++) {
            cout << res[i] << " ";
        }

        cout << "\n";
    }

    return 0;
}