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

    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<ll> b_sum(m + 1, 0);
    for (int i = 0; i < m; i++) {
        b_sum[i + 1] = b_sum[i] + b[i];
    }

    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll a_val = a[i];
        auto iter = lower_bound(b.begin(), b.end(), a_val);
        int geq_cnt = b.end() - iter;
        int lt_cnt = m - geq_cnt;
        ll b_lt_sum = b_sum[lt_cnt];
        ll b_geq_sum = b_sum[m] - b_lt_sum;
        res += a_val * lt_cnt - b_lt_sum + b_geq_sum - a_val * geq_cnt;
        res %= MOD9;
    }

    cout << res;

    return 0;
}