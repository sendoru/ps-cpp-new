// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string a, b;
    cin >> a >> b;

    int ans = 123123;

    for (int offset = 0; offset < b.size() - a.size() + 1; offset++) {
        int cur = 0;
        string s = b.substr(offset, a.size());
        for (int i = 0; i < s.size(); i++) {
            if (a[i] != s[i]) {
                cur++;
            }
        }

        ans = min(ans, cur);
    }

    cout << ans << endl;

    return 0;
}