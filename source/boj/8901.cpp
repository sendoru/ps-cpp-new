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
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        ll ab, bc, ca;
        cin >> ab >> bc >> ca;
        ll ans = 0;
        // ab
        for (int i = 0; i <= min(a, b); i++) {
            ll tmp = i * ab;
            int tmpa = a - i;
            int tmpb = b - i;
            // priority: bc > ca
            if (bc >= ca) {
                // bc
                int bc_cnt = min(tmpb, c);
                tmp += bc_cnt * bc;
                tmpb -= bc_cnt;
                int tmpc = c - bc_cnt;
                // ca
                int ca_cnt = min(tmpa, tmpc);
                tmp += ca_cnt * ca;
            } else {
                // ca
                int ca_cnt = min(tmpa, c);
                tmp += ca_cnt * ca;
                tmpa -= ca_cnt;
                int tmpc = c - ca_cnt;
                // bc
                int bc_cnt = min(tmpb, tmpc);
                tmp += bc_cnt * bc;
            }
            ans = max(ans, tmp);
        }

        cout << ans << '\n';
    }

    return 0;
}