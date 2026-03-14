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

vector<ll> dp(1'000'010);

ll solve(ll l, ll r, ll d, ll u) {
    if (r <= 0 && l < 0) {
        return solve(-r, -l, d, u);
    }
    if (u <= 0 && d < 0) {
        return solve(l, r, -u, -d);
    }
    if (l == 0 && d == 0 && r >= 0 && u >= 0) {
        ll diff = max(r, u) - min(r, u);
        return dp[min(r, u)] + (min(r, u) + 1) * ((diff + (min(r, u) % 2 == 0 ? 0 : 1)) / 2);
    }
    if (l == 0 && r == 0) {
        return (u - d + (d % 2 == 0 ? 2 : 1)) / 2;
    }
    if (d == 0 && u == 0) {
        return (r - l + (l % 2 == 0 ? 2 : 1)) / 2;
    }

    // split
    if (l < 0 && r > 0) {
        return solve(0, -l, d, u) + solve(0, r, d, u) - solve(0, 0, d, u);
    }
    if (d < 0 && u > 0) {
        return solve(l, r, 0, -d) + solve(l, r, 0, u) - solve(l, r, 0, 0);
    }

    // inclusion-exclusion
    if (l > 0) {
        return solve(0, r, d, u) - solve(0, l - 1, d, u);
    }
    if (d > 0) {
        return solve(l, r, 0, u) - solve(l, r, 0, d - 1);
    }
    return -1; // should not reach here
}

ll solve_naive(ll l, ll r, ll d, ll u) {
    ll ans = 0;
    for (ll x = l; x <= r; x++) {
        for (ll y = d; y <= u; y++) {
            if (max(abs(x), abs(y)) % 2 == 0) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    dp[0] = 1;
    for (int i = 1; i < 1'000'010; i++) {
        dp[i] = dp[i - 1];
        if (i % 2 == 0) {
            dp[i] += 2 * i + 1;
        }
    }

#ifdef DEBUG
    for (int l = -10, r = -10; l <= 10; l++) {
        for (r = l; r <= 10; r++) {
            for (int d = -10, u = -10; d <= 10; d++) {
                for (u = d; u <= 10; u++) {
                    ll ans1 = solve(l, r, d, u);
                    ll ans2 = solve_naive(l, r, d, u);
                    if (ans1 != ans2) {
                        cout << "Mismatch: " << l << " " << r << " " << d << " " << u << " -> " << ans1 << " vs " << ans2 << "\n";
                    }
                }
            }
        }
    }
    cout << "Debug check completed.\n";
#endif

    ll l, r, d, u;
    cin >> l >> r >> d >> u;
    cout << solve(l, r, d, u);

    return 0;
}