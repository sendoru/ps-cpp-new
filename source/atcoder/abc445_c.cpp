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
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> dp(n + 1, -1);
    function<int(int)> dfs = [&](int i) {
        if (dp[i] != -1) {
            return dp[i];
        }
        if (a[i] == i) {
            return dp[i] = i;
        }
        return dp[i] = dfs(a[i]);
    };

    for (int i = 1; i <= n; i++) {
        cout << dfs(i) << ' ';
    }

    return 0;
}