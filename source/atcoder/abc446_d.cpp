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
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    map<ll, int> pre;
    for (int i = 0; i < n; i++) {
        if (pre.count(a[i] - 1)) {
            ans = max(ans, pre[a[i] - 1] + 1);
        } else {
            ans = max(ans, 1);
        }
        pre[a[i]] = max(pre[a[i]], pre[a[i] - 1] + 1);
    }

    cout << ans << '\n';

    return 0;
}