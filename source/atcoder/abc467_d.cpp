// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool is_parallel(array<ld, 2> pq, array<ld, 2> rs) {
    return pq[0] * rs[1] == pq[1] * rs[0];
}

bool is_vertical(array<ld, 2> pq, array<ld, 2> rs) {
    return pq[0] * rs[0] + pq[1] * rs[1] == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        vector<array<ld, 2>> dots(4);
        for (int i = 0; i < 4; i++) {
            cin >> dots[i][0] >> dots[i][1];
        }
        array<ld, 2> pq = {dots[1][0] - dots[0][0], dots[1][1] - dots[0][1]};
        array<ld, 2> rs = {dots[3][0] - dots[2][0], dots[3][1] - dots[2][1]};
        if (!is_parallel(pq, rs)) {
            cout << "Yes\n";
            continue;
        }
        array<ld, 2> pq_mid = {(dots[0][0] + dots[1][0]) / 2, (dots[0][1] + dots[1][1]) / 2};
        array<ld, 2> rs_mid = {(dots[2][0] + dots[3][0]) / 2, (dots[2][1] + dots[3][1]) / 2};
        array<ld, 2> mid_to_mid = {rs_mid[0] - pq_mid[0], rs_mid[1] - pq_mid[1]};
        if (pq_mid == rs_mid || is_vertical(pq, mid_to_mid)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}