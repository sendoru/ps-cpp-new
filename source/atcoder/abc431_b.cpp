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

    int x, n;
    cin >> x >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    int q;
    cin >> q;

    int ans = 0;
    vector<bool> used(n, false);
    while (q--) {
        int p;
        cin >> p;
        p--;
        if (used[p]) {
            ans -= w[p];
            used[p] = false;
        } else {
            ans += w[p];
            used[p] = true;
        }
        cout << x + ans << '\n';
    }

    return 0;
}