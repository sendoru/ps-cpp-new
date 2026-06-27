// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll fact[100], inv_fact[100];

ll mod9pow(ll b, ll e)
{
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = (res * b) % MOD9;
        }
        b = (b * b) % MOD9;
        e >>= 1;
    }
    return res;
}

ll mod9inv(ll x)
{
    return mod9pow(x, MOD9 - 2);
}

ll comb(ll n, ll r)
{
    if (n < r || n < 0 || r < 0) {
        return 0;
    }
    return (((fact[n] * inv_fact[r]) % MOD9) * inv_fact[n - r]) % MOD9;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i < 100; i++) {
        fact[i] = (fact[i - 1] * i) % MOD9;
    }
    inv_fact[99] = mod9inv(fact[99]);
    for (int i = 98; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD9;
    }

    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l_size = n / 2, r_size = n - l_size;

    vector<vector<ll>> left(l_size + 1), right(r_size + 1);
    for (int i = 0; i < (1 << l_size); i++) {
        ll sum = 0;
        ll subset_size = __builtin_popcount(i);
        for (int j = 0; j < l_size; j++) {
            if (i & (1 << j)) {
                sum += a[j];
            }
        }
        left[subset_size].push_back(sum);
    }

    vector<vector<ll>> left_pf_sum(l_size + 1);
    for (int i = 0; i <= l_size; i++) {
        sort(left[i].begin(), left[i].end());
        left_pf_sum[i].resize(left[i].size() + 1);
        for (int j = 0; j < left[i].size(); j++) {
            left_pf_sum[i][j + 1] = left_pf_sum[i][j] + left[i][j];
        }
    }

    for (int i = 0; i < (1 << r_size); i++) {
        ll sum = 0;
        ll subset_size = __builtin_popcount(i);
        for (int j = 0; j < r_size; j++) {
            if (i & (1 << j)) {
                sum += a[l_size + j];
            }
        }
        right[subset_size].push_back(sum);
    }

    for (int i = 0; i <= r_size; i++) {
        sort(right[i].begin(), right[i].end());
    }

    vector<ll> cnts(n + 1);
    vector<ll> sums(n + 1);

    for (int l_cnt = 0; l_cnt <= l_size; l_cnt++) {
        for (int r_cnt = 0; r_cnt <= r_size; r_cnt++) {
            ll p = left[l_cnt].size();
            for (ll a_r : right[r_cnt]) {
                while (p > 0 && left[l_cnt][p - 1] + a_r >= x) {
                    p--;
                }
                if (p == 0) {
                    break;
                }

                ll cnt = l_cnt + r_cnt;
                cnts[cnt] += p;
                cnts[cnt] %= MOD9;
                sums[cnt] += (left_pf_sum[l_cnt][p] + a_r % MOD9 * p) % MOD9;
                sums[cnt] %= MOD9;
            }
        }
    }

    ll ans = 0;
    ll total_sum = accumulate(a.begin(), a.end(), 0LL) % MOD9;
    for (int cnt = 0; cnt <= n - 1; cnt++) {
        if (cnts[cnt] == 0) {
            continue;
        }
        ll ways = (cnts[cnt] * total_sum) % MOD9 - sums[cnt];
        ways = (ways % MOD9 + MOD9) % MOD9;

        ll prob = mod9inv(n) * mod9inv(comb(n - 1, cnt)) % MOD9;
        ans += (ways * prob) % MOD9;
        ans %= MOD9;
    }

    cout << ans << '\n';

    return 0;
}