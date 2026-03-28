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
    vector<int> ans(m + 1);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        ans[a]--;
        ans[b]++;
    }

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}