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

    ll n, m;
    cin >> n >> m;
    vector<ll> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
    }

    vector<ll> ans(n, n - 1);
    for (int i = 0; i < m; i++) {
        ans[a[i]]--;
        ans[b[i]]--;
    }
    for (int i = 0; i < n; i++) {
        ans[i] = ans[i] * (ans[i] - 1) * (ans[i] - 2) / 6;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}