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

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        b[i]--;
    }

    int m;
    cin >> m;
    vector<string> s(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }

    vector<array<bool, 26>> cands(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[j].length() == a[i]) {
                cands[i][s[j][b[i]] - 'a'] = true;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (s[i].length() != n) {
            cout << "No\n";
            continue;
        }

        bool ok = true;
        for (int j = 0; j < n; j++) {
            if (!cands[j][s[i][j] - 'a']) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "Yes\n" : "No\n");
    }

    return 0;
}