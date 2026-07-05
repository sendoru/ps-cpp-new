// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    if (m == 1) {
        if (n > 26) {
            cout << "NO\n";
            return 0;
        }
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << (char)('A' + i) << '\n';
        }
        return 0;
    }

    if (n > 10) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";

    string vow = "AEIOU", con = "BCDFG";
    vector<string> base;
    for (int i = 0; i < 5; i++) {
        base.push_back(string(1, vow[i]) + string(1, con[i]));
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            base[i] = base[i] + base[i];
        }
        base.push_back(base[i]);
        reverse(base[5 + i].begin(), base[5 + i].end());
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << base[i][j];
        }
        cout << "\n";
    }

    return 0;
}