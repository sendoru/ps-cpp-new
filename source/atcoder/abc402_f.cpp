// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = (res * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    if (n == 1) {
        cout << a[0][0] % m << endl;
        return 0;
    }

    // mitn on diag
    vector<vector<int>> first_half(n), second_half(n);

    for (int i = 0; i < (1 << (n - 1)); i++) {
        // (0, 0) to diag
        // 옆으로 pop_cnt번, 아래로 (n - pop_cnt)번
        int pop_cnt = __builtin_popcount(i);
        ll cur = 0;
        ll r = 0, c = 0;
        for (int j = 0; j < n - 1; j++) {
            cur = (cur * 10 + a[r][c]) % m;
            if (i & (1 << j)) {
                r++;
            } else {
                c++;
            }
        }
        first_half[pop_cnt].push_back(cur);

        // diag to (n - 1, n - 1)
        // 옆으로 (n - pop_cnt)번, 아래로 pop_cnt번
        cur = 0;
        for (int j = 0; j < n - 1; j++) {
            cur = (cur * 10 + a[r][c]) % m;
            if (i & (1 << j)) {
                c++;
            } else {
                r++;
            }
        }
        cur = (cur * 10 + a[n - 1][n - 1]) % m;
        second_half[pop_cnt].push_back(cur);
    }

    for (auto &elem : first_half) {
        sort(elem.begin(), elem.end());
    }
    for (auto &elem : second_half) {
        sort(elem.begin(), elem.end());
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (auto first : first_half[i]) {

            first = (first * modpow(10, n, m)) % m;
            ll target = m - first - 1;

            auto it = upper_bound(second_half[i].begin(), second_half[i].end(), target);
            if (it != second_half[i].begin()) {
                it--;
                ans = max(ans, (ll)(first + *it) % m);
            }
            ans = max(ans, (ll)(first + second_half[i].back()) % m);
        }
    }

    cout << ans << endl;

    return 0;
}