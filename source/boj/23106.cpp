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

bool check(vector<vector<ll>> &ans) {
    vector<ll> sums(ans.size());
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            sums[i] += ans[i][j];
        }
    }
    for (int i = 0; i < (int)sums.size() - 1; i++) {
        if (sums[i] != sums[i + 1]) {
            return false;
        }
    }

    return true;
}

vector<vector<ll>> solve(ll n) {
    vector<vector<ll>> ret;
    if (n <= 3) {
        return ret;
    }

    if (n % 2 == 0) {
        for (int i = 0; i < n / 2; i++) {
            ret.push_back({2 * i + 1, 2 * n - 2 * i - 1});
        }
        return ret;
    }

    for (int div = 3; div * div <= n; div++) {
        if (n % div == 0) {
            ret = vector<vector<ll>>(div);
            ll m = n / div;
            for (int i = 0, j = div / 2; i < div; i++, j = (j + 1) % div) {
                ret[i + j - (div) / 2].push_back(2 * i + 1);
                ret[i + j - (div) / 2].push_back(2 * (j + div) + 1);
            }

            for (int i = 2; i < n / div; i++) {
                for (int j = 0; j < div; j++) {
                    int idx;
                    if (i % 2 == 0) {
                        idx = i * div + div - j - 1;
                    } else {
                        idx = i * div + j;
                    }
                    ret[j].push_back(2 * idx + 1);
                }
            }
            return ret;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    for (int i = 2; i < 12345; i++) {
        auto ans = solve(i);
        assert(check(ans));
    }
#endif

    ll n;
    cin >> n;
    auto ans = solve(n);
    if (ans.size() == 0) {
        cout << -1;
        return 0;
    }

    cout << ans.size() << '\n';
    for (auto &v : ans) {
        cout << v.size() << ' ';
        for (auto &x : v) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}