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

    string s;
    cin >> s;

    int ans = 0;
    char next = 'i';
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != next) {
            ans++;
        }
        else {
            if (next == 'i') {
                next = 'o';
            }
            else {
                next = 'i';
            }
        }
    }
    if (s.back() == 'i') {
        ans++;
    }

    cout << ans;

    return 0;
}