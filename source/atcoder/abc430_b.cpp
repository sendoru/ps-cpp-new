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
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    set<vector<string>> p;
    for (int r0 = 0; r0 <= n - m; r0++) {
        for (int c0 = 0; c0 <= n - m; c0++) {
            vector<string> t;
            for (int i = 0; i < m; i++) {
                t.push_back(s[r0 + i].substr(c0, m));
            }
            p.insert(t);
        }
    }

    cout << p.size() << "\n";

    return 0;
}