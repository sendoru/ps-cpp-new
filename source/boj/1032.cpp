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
    string ans;
    cin >> ans;
    for (int i = 1; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < (int)ans.size(); j++) {
            if (ans[j] != s[j]) {
                ans[j] = '?';
            }
        }
    }

    cout << ans;

    return 0;
}