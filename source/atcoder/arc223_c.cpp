#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll op_sum(ll a, ll b) { return a + b; }
ll e_sum() { return 0; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<ll> rem_cnt(n);
        bool possible = true;
        for (int i = 0; i < n; i++) {
            rem_cnt[a[i] % n]++;
            if (rem_cnt[a[i] % n] > 1) {
                possible = false;
                break;
            }
        }
        if (!possible) {
            cout << 0 << "\n";
            continue;
        }

        vector<ll> rem(n);
        for (int i = 0; i < n; i++) {
            rem[i] = a[i] % n;
        }
        ll ans = 1;
        for (ll i = 2; i <= n - 1; i++) {
            ans = ans * modpow(i, n - i, n) % n;
        }

        atcoder::segtree<ll, op_sum, e_sum> inv_counter(n);
        ll inv_parity = 0;
        for (int i = 0; i < n; i++) {
            ll inv_cnt = inv_counter.prod(rem[i], n);
            inv_parity ^= (inv_cnt % 2);
            inv_counter.set(rem[i], 1);
        }

        if (inv_parity) {
            ans = (n - ans) % n;
        }

        cout << ans << "\n";
    }

    return 0;
}