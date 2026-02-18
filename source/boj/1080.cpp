// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

void flip(vector<vector<int>> &A, int x, int y) {
    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            A[i][j] = 1 - A[i][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m)), B(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            A[i][j] = s[j] - '0';
        }
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            B[i][j] = s[j] - '0';
        }
    }

    vector<vector<bool>> fliped(n, vector<bool>(m));
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < m - 2; j++) {
            if (A[i][j] != B[i][j]) {
                flip(A, i, j);
                fliped[i][j] = 1 - fliped[i][j];
            }
        }
    }

    if (A != B) {
        cout << -1 << "\n";
    } else {
        int ans = 0;
        for (int i = 0; i < n - 2; i++) {
            for (int j = 0; j < m - 2; j++) {
                if (fliped[i][j]) {
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}