// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll comb(ll n, ll k) {
    if (k > n)
        return 0;
    if (k > n - k) {
        k = n - k;
    }
    ll res = 1;
    for (ll i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> forest_cnt(n + 1);
    forest_cnt[0] = 1;
    for (ll i = 1; i <= n; i += 2) {
        ll tree_cnt = forest_cnt[i - 1];
        if (tree_cnt == 0) {
            continue;
        }
        auto nxt_forest_cnt = forest_cnt;
        for (ll j = 0; j <= n; j++) {
            for (ll k = 1; j + i * k <= n; k++) {
                nxt_forest_cnt[j + i * k] += forest_cnt[j] * comb(tree_cnt + k - 1, k);
            }
        }
        forest_cnt = nxt_forest_cnt;
    }

    cout << forest_cnt[n] << "\n";

    return 0;
}