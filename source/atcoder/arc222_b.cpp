// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(vector<ll> &rsp) {
    ll zero_cnt = (rsp[0] == 0) + (rsp[1] == 0) + (rsp[2] == 0);
    if (zero_cnt == 2) {
        return 0;
    }
    if (zero_cnt == 1) {
        if (rsp[0] == 0) {
            if (rsp[1] > rsp[2]) {
                return rsp[2] - 1;
            }
            return rsp[1];
        }
        if (rsp[1] == 0) {
            if (rsp[2] > rsp[0]) {
                return rsp[0] - 1;
            }
            return rsp[2];
        }
        if (rsp[2] == 0) {
            if (rsp[0] > rsp[1]) {
                return rsp[1] - 1;
            }
            return rsp[0];
        }
    }

    ll ans = 0;

    // only r wins
    if (rsp[1] >= 2) {
        ans = max(ans, min(rsp[0], rsp[1] - 1));
    }
    // only s wins
    if (rsp[2] >= 2) {
        ans = max(ans, min(rsp[1], rsp[2] - 1));
    }
    // only p wins
    if (rsp[0] >= 2) {
        ans = max(ans, min(rsp[2], rsp[0] - 1));
    }

    // r and s win
    if (rsp[1] >= 3 && rsp[2] >= 2) {
        ans = max(ans, min({rsp[0] + rsp[2] - 1, rsp[1] - 1}));
    }
    // s and p win
    if (rsp[2] >= 3 && rsp[0] >= 2) {
        ans = max(ans, min({rsp[1] + rsp[0] - 1, rsp[2] - 1}));
    }
    // p and r win
    if (rsp[0] >= 3 && rsp[1] >= 2) {
        ans = max(ans, min({rsp[2] + rsp[1] - 1, rsp[0] - 1}));
    }

    if (rsp[0] >= 3 && rsp[1] >= 3 && rsp[2] >= 3) {
        ans = max(ans, min({rsp[0] + rsp[1] - 3, rsp[1] + rsp[2] - 3, rsp[2] + rsp[0] - 3, (rsp[0] + rsp[1] + rsp[2] - 3) / 2}));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        vector<ll> rsp(3);
        for (int i = 0; i < 3; i++) {
            cin >> rsp[i];
        }
        cout << solve(rsp) << "\n";
    }

    return 0;
}