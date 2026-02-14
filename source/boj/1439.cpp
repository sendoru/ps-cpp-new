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

    string s;
    cin >> s;
    string s_comp;
    s_comp += s[0];
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] != s[i - 1]) {
            s_comp += s[i];
        }
    }

    cout << s_comp.size() / 2;

    return 0;
}