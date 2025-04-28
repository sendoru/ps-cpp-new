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

    string t, u;
    cin >> t >> u;

    bool ans = false;

    for (int i = 0; i < t.size() - u.size() + 1; i++) {
        bool ok = true;
        for (int j = 0; j < u.size(); j++) {
            if (t[i + j] != '?' && t[i + j] != u[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = true;
            break;
        }
    }

    cout << (ans ? "Yes" : "No") << endl;

    return 0;
}