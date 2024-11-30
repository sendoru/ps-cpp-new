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
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    vector<int> a_min(n);
    a_min[0] = a[0];
    for (int i = 1; i < n; i++) {
        a_min[i] = min(a_min[i - 1], a[i]);
    }

    vector<int> ans(m);
    for (int i = 0; i < m; i++) {
        ans[i] = lower_bound(a_min.begin(), a_min.end(), b[i], greater<>()) - a_min.begin();
        if (ans[i] == n) {
            ans[i] = -2;
        }
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] + 1 << '\n';
    }

    return 0;
}