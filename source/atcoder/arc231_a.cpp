// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Event {
    ll x, y, z;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<vector<ll>> dist_sqaures(501, vector<ll>(501));
    for (int i = 0; i <= 500; i++) {
        for (int j = 0; j <= 500; j++) {
            dist_sqaures[i][j] = (ll)(i - j) * (i - j);
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Event> events(n);
        for (int i = 0; i < n; i++) {
            cin >> events[i].x >> events[i].y >> events[i].z;
        }

        vector<vector<ll>> opts(501, vector<ll>(501, 1e18));
        for (int y = 0; y <= 500; y++) {
            opts[0][y] = dist_sqaures[0][y];
        }

        ll sum_z = 0;
        ll min_omo = 0;

        for (auto [x, y, z] : events) {
            ll query_val = 1e18;
            for (int i = 0; i <= 500; i++) {
                query_val = min(query_val, opts[i][y] + dist_sqaures[x][i]);
            }

            ll opt_minus_offset = query_val - z;
            sum_z += z;
            min_omo = min(min_omo, opt_minus_offset);

            for (int i = 0; i <= 500; i++) {
                opts[x][i] = min(opts[x][i], opt_minus_offset + dist_sqaures[i][y]);
            }
        }

        cout << sum_z + min_omo << '\n';
    }

    return 0;
}