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

    int n, k;
    cin >> n >> k;
    vector<vector<int>> v(n, vector<int>(k));
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        vector<int> vi(k);
        for (int j = 0; j < k; j++) {
            vi[j] = (t >> j) & 1;
        }
        v[i] = vi;
    }

    int ans = 0;
    vector<int> cur(k);
    map<vector<int>, vector<int>> m;
    m[cur].push_back(-1);
    for (int i = 0; i < n; i++) {
        if (v[i] == vector<int>(k, 1)) {
            ans = max(ans, 1);
        }
        for (int j = 0; j < k; j++) {
            cur[j] += v[i][j];
        }
        vector<int> cur2(k);
        for (int j = 0; j < k; j++) {
            cur2[j] = cur[j] - cur[0];
        }
        cur = cur2;
        if (m.find(cur) != m.end()) {
            ans = max(ans, i - m[cur][0]);
        }
        m[cur].push_back(i);
    }
    cout << ans << endl;
    return 0;
}