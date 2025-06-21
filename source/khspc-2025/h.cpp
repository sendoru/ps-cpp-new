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
        ll n, x;
        cin >> n >> x;
        vector<ll> p(x);
        for (int i = 0; i < x; i++) {
            cin >> p[i];
        }

        vector<vector<ll>> groups(1);
        groups[0] = {p[0]};
        for (int i = 1; i < x; i++) {
            ll prev = p[i - 1];
            if (p[i] - prev <= 8) {
                groups.back().push_back(p[i]);
            } else {
                groups.push_back({p[i]});
            }
        }

        bool ans = true;
        for (int i = 0; i < groups.size(); i++) {
            vector<array<bool, 4>> dp;
            vector<bool> gasi;
            if (i == 0) {
                dp.resize(groups[i].back() + 1);
                gasi.resize(groups[i].back() + 1, false);
                dp[0] = {true, false, false, false};
                for (int p : groups[i]) {
                    gasi[p] = true;
                }

                for (int j = 1; j <= groups[i].back(); j++) {
                    dp[j] = {false, false, false, false};
                    dp[j][0] = !gasi[j] && (dp[j - 1][0] || dp[j - 1][3]);
                    for (int k = 1; k <= 3; k++) {
                        dp[j][k] = dp[j - 1][k - 1];
                    }
                }
                auto fin = dp.back();
                if (!fin[0] && !fin[1] && !fin[2] && !fin[3]) {
                    ans = false;
                    break;
                }
            } else {
                dp.resize(groups[i].back() - groups[i].front() + 1);
                gasi.resize(groups[i].back() - groups[i].front() + 1, false);
                dp[0] = {false, true, true, true};
                for (int p : groups[i]) {
                    gasi[p - groups[i].front()] = true;
                }

                for (int j = 1; j <= groups[i].back() - groups[i].front(); j++) {
                    dp[j] = {false, false, false, false};
                    dp[j][0] = gasi[j + groups[i].front()] && (dp[j - 1][0] || dp[j - 1][3]);
                    for (int k = 1; k <= 3; k++) {
                        dp[j][k] = dp[j - 1][k - 1];
                    }
                }
                auto fin = dp.back();
                if (!fin[0] && !fin[1] && !fin[2] && !fin[3]) {
                    ans = false;
                    break;
                }
            }
        }

        if (ans) {
            cout << "POSSIBLE\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}

// 1 1100000000000 1 1 123123123123