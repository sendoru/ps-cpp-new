// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int get_count(vector<vector<int>> &v, int r1, int c1, int r2, int c2, int num) {
    int ret = 0;
    for (int i = r1; i <= r2; i++) {
        for (int j = c1; j <= c2; j++) {
            ret += v[i][j] == num;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            v[i][j] = s[j] == 'R';
        }
    }

    // filp row so that v[i][0] == 0
    for (int i = 0; i < n; i++) {
        if (v[i][0] == 1) {
            for (int j = 0; j < n; j++) {
                v[i][j] = 1 - v[i][j];
            }
        }
    }

    // and column so that v[0][j] == 0
    for (int j = 0; j < n; j++) {
        if (v[0][j] == 1) {
            for (int i = 0; i < n; i++) {
                v[i][j] = 1 - v[i][j];
            }
        }
    }

    vector<pii> ans;

    if (get_count(v, 1, 1, n - 1, n - 1, 0) == 0) {
        ans.push_back({1, 1});
    }

    if (get_count(v, 1, 1, n - 1, n - 1, 1) == 1) {
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (v[i][j] == 1) {
                    ans.push_back({i + 1, j + 1});
                    continue;
                }
            }
        }
    }

    if (get_count(v, 1, 1, n - 1, n - 1, 1) == n - 1) {
        // filp a row so that only one 1 in the first column
        for (int i = 1; i < n; i++) {
            if (get_count(v, i, 1, i, n - 1, 0) == 0) {
                ans.push_back({i + 1, 1});
                continue;
            }
        }
        // or a column
        for (int i = 1; i < n; i++) {
            if (get_count(v, 1, i, n - 1, i, 0) == 0) {
                ans.push_back({1, i + 1});
                continue;
            }
        }
    }

    sort(ans.begin(), ans.end());
    if (ans.size() == 0) {
        cout << -1 << endl;
    } else {
        cout << ans[0].first << " " << ans[0].second << endl;
    }
    return 0;
}