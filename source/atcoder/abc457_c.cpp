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

    ll n, k;
    cin >> n >> k;
    vector<vector<ll>> a(n);
    for (int i = 0; i < n; i++) {
        ll l;
        cin >> l;
        a[i].resize(l);
        for (int j = 0; j < l; j++) {
            cin >> a[i][j];
        }
    }

    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    k--;
    for (int i = 0; i < n; i++) {
        if (k < a[i].size() * c[i]) {
            cout << a[i][k % a[i].size()];
            break;
        }
        k -= a[i].size() * c[i];
    }

    return 0;
}