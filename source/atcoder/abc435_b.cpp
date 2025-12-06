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

    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> pf_sum(n);
    pf_sum[0] = a[0];
    for(ll i = 1; i < n; i++) {
        pf_sum[i] = pf_sum[i - 1] + a[i];
    }

    int ans = 0;
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            ll sum = l == 0? pf_sum[r] : pf_sum[r] - pf_sum[l - 1];
            bool flag = true;
            for (int i = l; i <= r; i++) {
                if (sum % a[i] == 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ans++;
            }
        }
    }

    cout << ans << "\n";

    return 0;
}