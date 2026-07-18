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

    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(n - 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> b[i];
    }
    vector<ll> mod_diff(n);
    for (int i = 1; i < n; i++) {
        mod_diff[i] = b[i - 1] - a[i] - a[i - 1] - mod_diff[i - 1];
        mod_diff[i] = (mod_diff[i] % m + m) % m;
    }
    vector<ll> cands;
    for (int i = 0; i < n; i += 2) {
        cands.push_back((m - mod_diff[i]) % m);
    }
    vector<ll> odds;
    for (int i = 1; i < n; i += 2) {
        odds.push_back(mod_diff[i]);
    }
    sort(odds.begin(), odds.end());
    sort(cands.begin(), cands.end());
    // cands.erase(unique(cands.begin(), cands.end()), cands.end());
    ll cur_sum = accumulate(mod_diff.begin(), mod_diff.end(), 0LL);
    ll ans = cur_sum;
    ll cur_d0 = 0;
    int i = 1;
    while (i < cands.size() && cands[i] == 0) {
        i++;
    }
    for (int odd_idx = 0; i < cands.size(); i++) {
        while (odd_idx < odds.size() && odds[odd_idx] < cands[i]) {
            cur_sum += m;
            odd_idx++;
        }
        cur_sum -= m;
        if (n % 2 == 1) {
            cur_sum += cands[i] - cands[i - 1];
        }
        ans = min(ans, cur_sum);
    }
    cout << ans;
    return 0;
}