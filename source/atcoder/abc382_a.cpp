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
    string s;
    cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '@') {
            ans++;
        }
    }

    ans -= m;
    ans = n - ans;
    cout << ans;

    return 0;
}