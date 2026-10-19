// #include "atcoder/all"
#include <bits/stdc++.h>

// #define DEBUG

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

    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i + 1];
    }

    vector<ll> sum1(n + 1), sum2(n + 1);
    for (int i = 0; i < n; i++) {
        sum1[i + 1] = sum1[i] + a[i + 1];
    }
    for (int i = 0; i < n; i++) {
        sum2[i + 1] = sum2[i] + sum1[i + 1];
    }

    vector<ll> outer_idx(n + 1);
    outer_idx[1] = 1;
    for (int i = 2; i <= n; i++) {
        outer_idx[i] = outer_idx[i - 1] + (i - 1);
    }

    // a1
    // a1 a2
    // a1 a2 a3
    // a1 a2 a3 a4
    // .....

#ifdef DEBUG
    vector<ll> b = {0};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            b.push_back(a[j]);
        }
    }

    for (int i = 1; i < b.size(); i++) {
        for (int j = i; j < b.size(); j++) {
            ll l = i, r = j;
            ll outer_l = upper_bound(outer_idx.begin(), outer_idx.end(), l) - outer_idx.begin() - 1;
            ll outer_r = upper_bound(outer_idx.begin(), outer_idx.end(), r) - outer_idx.begin() - 1;
            ll inner_l = l - outer_idx[outer_l];
            ll inner_r = r - outer_idx[outer_r];
            ll ans = sum2[outer_r] - sum2[outer_l - 1] - sum1[inner_l] - (sum2[outer_r] - sum2[outer_r - 1]) + sum1[inner_r + 1];

            ll ans_naive = 0;
            for (int k = l; k <= r; k++) {
                ans_naive += b[k];
            }
            if (ans != ans_naive) {
                cout << "l: " << l << ", r: " << r << ", ans: " << ans << ", ans_naive: " << ans_naive << "\n";
            }
        }
    }
#endif

    while (q--) {
        ll l, r;
        cin >> l >> r;
        ll outer_l = upper_bound(outer_idx.begin(), outer_idx.end(), l) - outer_idx.begin() - 1;
        ll outer_r = upper_bound(outer_idx.begin(), outer_idx.end(), r) - outer_idx.begin() - 1;
        ll inner_l = l - outer_idx[outer_l];
        ll inner_r = r - outer_idx[outer_r];
        ll ans = sum2[outer_r] - sum2[outer_l - 1] - sum1[inner_l] - (sum2[outer_r] - sum2[outer_r - 1]) + sum1[inner_r + 1];

        cout << ans << "\n";
    }

    return 0;
}