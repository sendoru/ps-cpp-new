// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> calc_weight(const vector<ll>& a) {
    ll n = a.size();
    vector<ll> pf_sum(n + 1), pf_sum2(n + 1);
    for (ll i = 0; i < n; i++) {
        pf_sum[i + 1] = pf_sum[i] + a[i];
        pf_sum2[i + 1] = pf_sum2[i] + i * a[i];
    }

    vector<ll> res(n);

    // calculating integral of field under V-shaped function
    for (int i = 0; i < n; i++) {
        ll left = i * pf_sum[i + 1] - pf_sum2[i + 1];
        ll right = (pf_sum2[n] - pf_sum2[i + 1]) - i * (pf_sum[n] - pf_sum[i + 1]);
        res[i] = left + right;
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (ll i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<ll> diag1(2 * n + 2), diag2(2 * n + 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            diag1[i + j] += a[i] * b[j] % m;
            diag2[i - j + n] += a[i] * b[j] % m;
        }
    }

    auto w1 = calc_weight(diag1), w2 = calc_weight(diag2);

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            ll f = (w1[i + j] + w2[i - j + n]) / 2;
            ans ^= (f + i * n + j);
        }
    }

    cout << ans;

    return 0;
}