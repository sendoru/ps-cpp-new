// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve_or(const vector<ll>& a) {
    ll n = a.size();
    ll res = 0;
    for (int i = 0; i < 31; i++) {
        ll cnt = n * (n + 1) / 2;
        ll zero_len = 0;
        for (int j = 0; j < n; j++) {
            if (((a[j] >> i) & 1) == 0) {
                zero_len++;
            } else {
                cnt -= zero_len * (zero_len + 1) / 2;
                zero_len = 0;
            }
        }
        cnt -= zero_len * (zero_len + 1) / 2;
        cnt %= MOD9;
        res += (1LL << i) * cnt;
        res %= MOD9;
    }
    return res;
}

ll solve_and(const vector<ll>& a) {
    ll n = a.size();
    ll res = 0;
    for (int i = 0; i < 31; i++) {
        ll cnt = 0;
        ll one_len = 0;
        for (int j = 0; j < n; j++) {
            if (((a[j] >> i) & 1) == 1) {
                one_len++;
            } else {
                cnt += one_len * (one_len + 1) / 2;
                one_len = 0;
            }
        }
        cnt += one_len * (one_len + 1) / 2;
        cnt %= MOD9;
        res += (1LL << i) * cnt;
        res %= MOD9;
    }
    return res;
}

ll solve_xor(const vector<ll>& a) {
    ll n = a.size();
    ll res = 0;
    for (int i = 0; i < 31; i++) {
        vector<int> pf_sum(n + 1, 0);
        for (int j = 0; j < n; j++) {
            pf_sum[j + 1] = pf_sum[j] + ((a[j] >> i) & 1);
        }
        ll cnt = 0;
        vector<int> cnt_mod(2, 0);
        for (int j = 0; j < n + 1; j++) {
            cnt += cnt_mod[1 - pf_sum[j] % 2];
            cnt_mod[pf_sum[j] % 2]++;
        }
        cnt %= MOD9;
        res += (1LL << i) * cnt;
        res %= MOD9;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << solve_and(a) << ' ' << solve_or(a) << ' ' << solve_xor(a) << '\n';

    return 0;
}