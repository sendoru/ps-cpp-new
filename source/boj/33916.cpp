// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const int MAX_N = 5000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<array<int, MAX_N + 1>> factors(MAX_N + 1);
    factors[2][2] = 1;
    for (int i = 3; i <= MAX_N; i++) {
        factors[i] = factors[i - 1];
        int x = i;
        for (int j = 2; j * j <= x; j++) {
            while (x % j == 0) {
                factors[i][j]++;
                x /= j;
            }
        }
        if (x > 1) {
            factors[i][x]++;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n1, r1, n2, r2;
        cin >> n1 >> r1 >> n2 >> r2;
        array<int, MAX_N + 1> f1, f2;

        f1 = factors[n1];
        for (int i = 2; i <= r1; i++) {
            f1[i] -= factors[r1][i];
        }
        for (int i = 2; i <= n1 - r1; i++) {
            f1[i] -= factors[n1 - r1][i];
        }

        f2 = factors[n2];
        for (int i = 2; i <= r2; i++) {
            f2[i] -= factors[r2][i];
        }
        for (int i = 2; i <= n2 - r2; i++) {
            f2[i] -= factors[n2 - r2][i];
        }

        bool is_coprime = true;
        for (int i = 2; i <= MAX_N; i++) {
            if (f1[i] > 0 && f2[i] > 0) {
                is_coprime = false;
                break;
            }
        }

        cout << (int)is_coprime << "\n";
    }

    return 0;
}