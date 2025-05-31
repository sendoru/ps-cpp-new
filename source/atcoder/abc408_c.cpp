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
    vector<ll> cnt(n + 2);
    for (int i = 0; i < m; i++) {
        ll l, r;
        cin >> l >> r;
        cnt[l]++;
        cnt[r + 1]--;
    }

    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
    }

    ll ans = MOD1;

    for (int i = 1; i <= n; i++) {
        ans = min(ans, cnt[i]);
    }

    cout << ans;

    return 0;
}