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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(n)), b(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }

    vector<vector<int>> diff(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            diff[i][j] = abs(a[i][j] - b[i][j]);
        }
    }

    // axis = column
    vector<int> max_diff(n);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            max_diff[j] = max(max_diff[j], diff[i][j]);
        }
    }

    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int col;
        cin >> col;
        ans += max_diff[col - 1];
    }

    cout << ans;

    return 0;
}