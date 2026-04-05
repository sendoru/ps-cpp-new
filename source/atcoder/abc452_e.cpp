// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll BOUND = 1000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    vector<ll> a_pf_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        a_pf_sum[i] = a_pf_sum[i - 1] + a[i];
        a_pf_sum[i] %= MOD9;
    }

    // 1 * a[1] + 2 * a[2] + ... + n * a[n]
    vector<ll> ai_pf_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        ai_pf_sum[i] = ai_pf_sum[i - 1] + a[i] * i;
        ai_pf_sum[i] %= MOD9;
    }

    // sum_by_mod[mod][idx] := sum of a[i] where i % mod == idx
    vector<vector<ll>> a_sum_by_mod(BOUND);
    for (int i = 1; i < BOUND; i++) {
        a_sum_by_mod[i].resize(i);
        for (int j = 0; j <= n; j++) {
            a_sum_by_mod[i][j % i] += a[j];
            a_sum_by_mod[i][j % i] %= MOD9;
        }
    }

    ll ans = 0;
    for (ll i = 1; i <= m; i++) {
        if (i < BOUND) {
            for (ll j = 0; j < i; j++) {
                ans += a_sum_by_mod[i][j] * b[i] * j;
                ans %= MOD9;
            }
        } else {
            for (ll j = 0; j <= n; j += i) {
                ll added = (ai_pf_sum[min(n, j + i - 1)] - ai_pf_sum[j] - (a_pf_sum[min(n, j + i - 1)] - a_pf_sum[j]) * j) % MOD9;
                added = (MOD9 + added) % MOD9;
                added = added * b[i] % MOD9;
                ans += added;
                ans %= MOD9;
            }
        }
    }

    cout << ans;

    return 0;
}