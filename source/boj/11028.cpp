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

    vector<ll> pf_sum(20'000'001);

    for (ll i = 2; i <= 200'000; i++) {
        for (ll j = 1; j < i; j++) {
            ll cur = 2 * i * i + 2 * i * j;
            if (cur > 20'000'000) {
                break;
            }
            if (gcd(i, j) != 1 || (i - j) % 2 == 0) {
                continue;
            }
            while (cur <= 20'000'000) {
                pf_sum[cur]++;
                cur += 2 * i * i + 2 * i * j;
            }
        }
    }

    for (ll i = 1; i <= 20'000'000; i++) {
        if (pf_sum[i] > 1) {
            pf_sum[i] = 0;
        }
        pf_sum[i] += pf_sum[i - 1];
    }

    while (true) {
        ll n = -1;
        cin >> n;
        if (n < 0) {
            break;
        } else {
            cout << pf_sum[n] << "\n";
        }
        if (!cin.good()) {
            break;
        }
    }

    return 0;
}