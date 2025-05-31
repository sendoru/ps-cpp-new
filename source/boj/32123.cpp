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

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<int> pf_sum(2 * n, 0);
    pf_sum[0] = (s[0] == '1') ? 1 : -1;
    for (int i = 1; i < 2 * n; i++) {
        pf_sum[i] = pf_sum[i - 1] + ((s[i] == '1') ? 1 : -1);
    }

    vector<ll> pos(n + 2), neg(n + 2);
    for (int i = 0; i < 2 * n; i++) {
        if (pf_sum[i] > 0) {
            pos[pf_sum[i]]++;
        } else if (pf_sum[i] < 0) {
            neg[-pf_sum[i]]++;
        }
    }

    vector<ll> upper(n + 2, 0), lower(n + 2, 0);
    for (int i = n; i >= 0; i--) {
        upper[i] = upper[i + 1] + pos[i + 1];
        lower[i] = lower[i + 1] + neg[i + 1];
        if (i - 1 >= 0) {
            pos[i - 1] += pos[i + 1];
            neg[i - 1] += neg[i + 1];
        }
    }

    ll ans = 1e18;

    for (int i = 0, j = k; i <= k; i++, j--) {
        ll cur = upper[i] + lower[j];
        ans = min(ans, cur);
    }

    cout << ans << '\n';

    return 0;
}