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
    int ans = 0;
    int t_prev = 0;
    for (int i = 0; i < n; i++) {
        int t, v;
        cin >> t >> v;
        ans = max(0, ans - (t - t_prev));
        ans += v;

        t_prev = t;
    }

    cout << ans << '\n';

    return 0;
}