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

    int n;
    cin >> n;
    vector<array<bool, 10>> a(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int ai;
            cin >> ai;
            a[i][ai] = true;
        }
    }

    vector<vector<int>> pre(n, vector<int>(10, -1));
    for (int j = 0; j < 10; j++) {
        if (a[0][j]) {
            pre[0][j] = j;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                if (j == k || pre[i - 1][k] == -1 || !a[i][j]) {
                    continue;
                }
                pre[i][j] = k;
                break;
            }
        }
    }

    vector<int> ans;
    int cur = -1;
    for (int j = 0; j < 10; j++) {
        if (pre[n - 1][j] != -1) {
            cur = j;
        }
    }
    if (cur == -1) {
        cout << -1 << "\n";
        return 0;
    }
    for (int i = n - 1; i >= 0; i--) {
        ans.push_back(cur);
        cur = pre[i][cur];
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}