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

    int n;
    cin >> n;
    bool logined = false;
    int ans = 0;
    while (n--) {
        string s;
        cin >> s;
        if (s == "login") {
            logined = true;
        }
        else if (s == "logout") {
            logined = false;
        }
        else if (s == "private" && !logined) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}