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

    ll n, m, q;
    cin >> n >> m >> q;
    vector<ll> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    vector<ll> ab_sorted(n + m);
    for (int i = 0; i < n; i++) {
        ab_sorted[i] = a[i];
    }
    for (int i = 0; i < m; i++) {
        ab_sorted[n + i] = b[i];
    }
    sort(ab_sorted.begin(), ab_sorted.end());

    multiset<ll> small, medium, large;
    for (int i = 0; i < n / 2; i++) {
        small.insert(ab_sorted[i]);
    }
    for (int i = n / 2; i < n / 2 + m; i++) {
        medium.insert(ab_sorted[i]);
    }
    for (int i = n / 2 + m; i < n + m; i++) {
        large.insert(ab_sorted[i]);
    }

    ll all_sum = accumulate(ab_sorted.begin(), ab_sorted.end(), 0LL);
    ll remain_sum = 0;
    for (ll x : medium) {
        remain_sum += x;
    }

    while (q--) {
        ll t, i, x;
        cin >> t >> i >> x;
        i--;
        ll old_val;
        if (t == 1) {
            old_val = a[i];
            a[i] = x;
        } else {
            old_val = b[i];
            b[i] = x;
        }
        all_sum += x - old_val;
        if (small.find(old_val) != small.end()) {
            small.erase(small.find(old_val));
        } else if (medium.find(old_val) != medium.end()) {
            medium.erase(medium.find(old_val));
            remain_sum -= old_val;
        } else {
            large.erase(large.find(old_val));
        }

        if (!small.empty() && x <= *small.rbegin()) {
            small.insert(x);
        } else if (!large.empty() && x >= *large.begin()) {
            large.insert(x);
        } else {
            medium.insert(x);
            remain_sum += x;
        }

        while (small.size() > n / 2) {
            ll val = *small.rbegin();
            small.erase(small.find(val));
            medium.insert(val);
            remain_sum += val;
        }
        while (small.size() < n / 2) {
            ll val = *medium.begin();
            medium.erase(medium.find(val));
            remain_sum -= val;
            small.insert(val);
        }

        while (large.size() > n / 2) {
            ll val = *large.begin();
            large.erase(large.find(val));
            medium.insert(val);
            remain_sum += val;
        }
        while (large.size() < n / 2) {
            ll val = *medium.rbegin();
            medium.erase(medium.find(val));
            remain_sum -= val;
            large.insert(val);
        }

        cout << all_sum - remain_sum << '\n';
    }

    return 0;
}