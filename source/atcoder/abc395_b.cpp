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

    vector<string> ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i] += '#';
        }
    }

    for (int s = 1, e = n - 2; s <= e; s++, e--) {
        for (int i = s; i <= e; i++) {
            for (int j = s; j <= e; j++) {
                if (s % 2) {
                    ans[i][j] = '.';
                }
                else {
                    ans[i][j] = '#';
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}