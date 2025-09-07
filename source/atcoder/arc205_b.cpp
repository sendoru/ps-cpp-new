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
    vector<int> parity(n, (n + 1) % 2);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        parity[u] ^= 1;
        parity[v] ^= 1;
    }

    ll parity_sum = accumulate(parity.begin(), parity.end(), 0LL);
    ll ans = n * (n - 1) / 2 - parity_sum / 2;
    cout << ans << "\n";

    return 0;
}