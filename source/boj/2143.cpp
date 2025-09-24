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

    int t;
    cin >> t;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    map<ll, ll> a_cnt, b_cnt;
    for (int i = 0; i < n; i++) {
        int cur_sum = 0;
        for (int j = i; j < n; j++) {
            cur_sum += a[j];
            a_cnt[cur_sum]++;
        }
    }

    for (int i = 0; i < m; i++) {
        int cur_sum = 0;
        for (int j = i; j < m; j++) {
            cur_sum += b[j];
            b_cnt[cur_sum]++;
        }
    }

    ll ans = 0;
    for (auto [sum_a, cnt_a] : a_cnt) {
        ll sum_b = t - sum_a;
        if (b_cnt.count(sum_b)) {
            ans += (ll)cnt_a * b_cnt[sum_b];
        }
    }

    cout << ans;

    return 0;
}