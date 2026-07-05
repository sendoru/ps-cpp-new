// #include "atcoder/all"
// #define DEBUG
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<array<ll, 2>> solve_partial(vector<ll> &h) {
    vector<array<ll, 2>> ans;
    for (int i = 1; h[0] != 0 && h[1] != 0; i++) {
        ll target_div = (1ll << i);
        ll ab_gcd = __gcd(h[0], h[1]);
        if (h[0] == ab_gcd) {
            ans.push_back({0, 1});
            h[0] = 0;
            break;
        }
        if (h[1] == ab_gcd) {
            ans.push_back({1, 0});
            h[1] = 0;
            break;
        }
        if (h[0] % target_div != 0) {
            ans.push_back({0, 1});
            h[0] -= __gcd(h[0], h[1]);
        }
        if (h[1] % target_div != 0) {
            ans.push_back({1, 0});
            h[1] -= __gcd(h[0], h[1]);
        }
    }
    assert(ans.size() <= 40);
    return ans;
}

vector<array<ll, 2>> solve(vector<ll> h) {
    vector<array<ll, 2>> ans = solve_partial(h);
    int zero_idx = (h[0] == 0 ? 0 : 1);
    for (int i = 0; i < h.size(); i++) {
        if (h[i] == 0) {
            continue;
        }
        ans.push_back({i, zero_idx});
        h[i] = 0;
    }
    assert(ans.size() <= h.size() + 40);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<ll> dis(1e6 - 10000, 1e6);
    for (int i = 0; i < 100; i++) {
        vector<ll> h(2);
        for (int j = 0; j < 2; j++) {
            h[j] = dis(gen);
        }
        vector<array<ll, 2>> partial_ans = solve_partial(h);
        cout << "Partial ans size: " << partial_ans.size() << '\n';
    }
    cout << flush;
#endif

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> h(n);
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        vector<array<ll, 2>> ans = solve(h);
        cout << ans.size() << '\n';
        for (auto [a, b] : ans) {
            cout << a + 1 << ' ' << b + 1 << '\n';
        }
    }

    return 0;
}