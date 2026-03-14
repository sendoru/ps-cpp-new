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
    vector<ll> c(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    vector<ll> used(m);
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        used[a] += b;
        used[a] = min(used[a], c[a]);
    }
    cout << accumulate(used.begin(), used.end(), 0LL) << '\n';

    return 0;
}