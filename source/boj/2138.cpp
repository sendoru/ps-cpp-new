// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

void flip(string &s, int idx) {
    for (int i = idx; i < idx + 3; i++) {
        s[i] = (s[i] == '0' ? '1' : '0');
    }
}

ll solve(string s, string t) {
    ll ans = 0;
    for (int i = 0; i < s.size() - 2; i++) {
        if (s[i] != t[i]) {
            flip(s, i);
            ans++;
        }
    }
    if (s == t) {
        return ans;
    } else {
        return 1e18;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    s = "0" + s + "0";
    ll ans = 1e18;
    for (char c1 : {'0', '1'}) {
        for (char c2 : {'0', '1'}) {
            string t2 = c1 + t + c2;
            ans = min(ans, solve(s, t2));
        }
    }
    if (ans == 1e18) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}