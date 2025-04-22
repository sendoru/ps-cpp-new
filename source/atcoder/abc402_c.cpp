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
    vector<int> k(m);
    vector<vector<int>> ing_to_dishes(1e6);
    for (int i = 0; i < m; i++) {
        cin >> k[i];
        for (int j = 0; j < k[i]; j++) {
            int x;
            cin >> x;
            ing_to_dishes[x].push_back(i);
        }
    }

    int cur = 0;
    for (int i = 0; i < m; i++) {
        if (k[i] == 0) {
            cur++;
        }
    }

    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        int bi;
        cin >> bi;
        for (auto ing : ing_to_dishes[bi]) {
            k[ing]--;
            if (k[ing] == 0) {
                cur++;
            }
        }

        ans[i] = cur;
    }

    for (auto a : ans) {
        cout << a << "\n";
    }

    return 0;
}