// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool solve(vector<string> &s) {
    sort(s.begin(), s.end());
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i + 1].size() >= s[i].size() && s[i + 1].substr(0, s[i].size()) == s[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> s(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        cout << (solve(s) ? "YES" : "NO") << "\n";
    }

    return 0;
}