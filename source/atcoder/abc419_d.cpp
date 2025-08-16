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
    string s, t;
    cin >> s >> t;
    vector<int> imos(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        imos[l]++;
        imos[r + 1]--;
    }
    for (int i = 1; i <= n; i++) {
        imos[i] += imos[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        if (imos[i] % 2 == 1) {
            cout << t[i - 1];
        } else {
            cout << s[i - 1];
        }
    }

    return 0;
}