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
        int n;
        cin >> n;
        vector<vector<ll>> abc(n, vector<ll>(3));
        for (int i = 0; i < n; i++) {
            cin >> abc[i][2] >> abc[i][1] >> abc[i][0];
        }

        ll d1_min = 0, d1_max = 0, d2_min = 0, d2_max = 0;

        for (int i = 0; i < n; i++) {
            ll a = abc[i][0], b = abc[i][1], c = abc[i][2];
            if (b >= a + c) {
                d1_min += c;
                d1_max += c;
                d2_max += a;
                d2_min += a;
            }

            else {
                // div2에 몰아주기
                if (a >= b) {
                    d2_max += b;
                } else {
                    d2_max += a;
                    d1_min += min(c, b - a);
                }

                // div1에 몰아주기
                if (c >= b) {
                    d1_max += b;
                } else {
                    d1_max += c;
                    d2_min += min(a, b - c);
                }
            }
        }

        assert(d1_max - d1_min == d2_max - d2_min);

        if (d1_min > d2_min) {
            swap(d1_min, d2_min);
            swap(d1_max, d2_max);
        }
        if (d1_max < d2_min) {
            cout << d1_max << '\n';
        } else {
            cout << (d1_min + d2_max) / 2 << '\n';
        }
    }

    return 0;
}