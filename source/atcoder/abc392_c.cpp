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

    vector<int> p(n), q(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> q[i];
        q[i]--;
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[q[i]] = q[p[i]];
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}