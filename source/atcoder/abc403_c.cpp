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

    int n, m, q;
    cin >> n >> m >> q;

    vector<set<int>> s(n + 1);
    vector<bool> all_granted(n + 1, false);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            s[x].insert(y);
        } else if (t == 2) {
            int x;
            cin >> x;
            all_granted[x] = true;
        } else {
            int x, y;
            cin >> x >> y;
            if (all_granted[x]) {
                cout << "Yes" << '\n';
            } else {
                cout << (s[x].count(y) ? "Yes" : "No") << '\n';
            }
        }
    }

    return 0;
}