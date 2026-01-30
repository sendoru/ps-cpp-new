// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    b %= m;
    while (e > 0) {
        if (e & 1)
            res = (res * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

ll get_lineq_dof(vector<vector<ll>> &A, vector<ll> &b, ll p) {
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

    // return -1 if no solution
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        for (int j = 0; j < m; j++) {
            sum += A[i][j];
        }
        if (sum == 0 && b[i] != 0) {
            return -1;
        }
    }

    ll rank = 0;
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) {
            rank++;
        }
    }
    return m - rank;
}

int encode(int r, int c) {
    return r * (r + 1) / 2 + c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int s, l;
    cin >> s >> l;
    vector<vector<ll>> A;
    vector<ll> b;
    for (int r = 0; r < s - 1; r++) {
        for (int c = 0; c <= r; c++) {
            vector<ll> row(s * (s + 1) / 2, 0);
            row[encode(r, c)] = 1;
            row[encode(r + 1, c)] = 1;
            row[encode(r + 1, c + 1)] = 1;
            A.push_back(row);
            b.push_back(0);
        }
    }

    for (int i = 0; i < l; i++) {
        int r, c, v;
        cin >> r >> c >> v;
        r--;
        c--;
        vector<ll> row(s * (s + 1) / 2, 0);
        row[encode(r, c)] = 1;
        A.push_back(row);
        b.push_back(v);
    }

    ll dof = get_lineq_dof(A, b, 3);
    if (dof == -1) {
        cout << 0 << '\n';
    } else {
        cout << (ll)powl(3, dof) << '\n';
    }

    return 0;
}