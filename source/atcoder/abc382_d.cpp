// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<int>> solve(int n, int m) {
    // a[0] >= 1
    // a[i - 1] + 10 <= a[i]
    // a[n - 1] <= m

    // eq. to
    // a[0] >= 1
    // a[i - 1] <= a[i]
    // a[n - 1] <= m - 10 * (n - 1)
    // and then a[i] += 10 * i for all i

    vector<vector<int>> ans;
    function<void(int, int, vector<int>)> dfs = [&](int i, int prev, vector<int> a) {
        if (i == n) {
            ans.push_back(a);
            return;
        }

        for (int j = prev; j <= m - 10 * (n - 1); j++) {
            a.push_back(j);
            dfs(i + 1, j, a);
            a.pop_back();
        }
    };

    dfs(0, 1, vector<int>());

    for (auto &elem : ans) {
        for (int i = 0; i < elem.size(); i++) {
            elem[i] += 10 * i;
        }
    }

    sort(ans.begin(), ans.end());

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    auto ans = solve(n, m);
    cout << ans.size() << '\n';
    for (auto &elem : ans) {
        for (int i = 0; i < elem.size(); i++) {
            cout << elem[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}