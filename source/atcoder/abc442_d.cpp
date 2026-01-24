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
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> pf_sum(n + 1);
    for (int i = 0; i < n; i++) {
        pf_sum[i + 1] = pf_sum[i] + a[i];
    }

    while (q--) {
        ll qt;
        cin >> qt;
        if (qt == 1) {
            ll x;
            cin >> x;
            pf_sum[x] = pf_sum[x] + a[x] - a[x - 1];
            swap(a[x], a[x - 1]);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << pf_sum[r] - pf_sum[l - 1] << "\n";
        }
    }

    return 0;
}