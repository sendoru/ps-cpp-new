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
    vector<bool> l(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        l[i] = (x == 1);
    }

    int ans = n - 1;
    for (int i = 0; i < n; i++) {
        if (!l[i]) {
            ans--;
        } else {
            break;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (!l[i]) {
            ans--;
        } else {
            break;
        }
    }

    ans = max(ans, 0);
    cout << ans << '\n';

    return 0;
}