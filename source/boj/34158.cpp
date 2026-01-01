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

    vector<ll> grundy_vals(64);
    grundy_vals[0] = 0;
    grundy_vals[1] = 1;
    for (int i = 2; i < 64; i++) {
        set<ll> next_grundy;
        next_grundy.insert(0);
        ll cur = 0;
        for (int j = i - 1; j >= 0; j--) {
            cur ^= grundy_vals[j];
            next_grundy.insert(cur);
        }
        ll g = 0;
        while (next_grundy.count(g)) g++;
        grundy_vals[i] = g;
    }

    ll k, g;
    cin >> k >> g;
    while(g--) {
        ll l, r;
        cin >> l >> r;
        l--;

        ll grundy = 0, tree_depth = 1;
        while(l < r) {
            if (l & 1) {
                grundy ^= grundy_vals[tree_depth];
                l++;
            }
            if (r & 1) {
                grundy ^= grundy_vals[tree_depth];
                r--;
            }
            l >>= 1;
            r >>= 1;
            tree_depth++;
        }
        cout << (grundy ? "swlee0202" : "mj1000j") << '\n';
    }

    return 0;
}