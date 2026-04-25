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

    ll n, q;
    cin >> n >> q;

    vector<ll> pre(n + 1), nxt(n + 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = -i;
    }

    while (q--) {
        ll c, p;
        cin >> c >> p;
        nxt[p] = c;
        if (pre[c] > 0) {
            nxt[pre[c]] = 0;
        }
        pre[c] = p;
    }

    vector<ll> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        if (pre[i] < 0) {
            int idx = -pre[i];
            int cnt = 0;
            while (idx > 0) {
                idx = nxt[idx];
                cnt++;
            }
            ans[i] = cnt;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}