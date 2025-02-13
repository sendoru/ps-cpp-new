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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n % 4 == 0) {
        cout << "Yes" << endl;
    } else if (n % 2 == 1) {
        int sum_a = 0;
        for (int i = 0; i < n; i++) {
            sum_a += a[i];
        }
        cout << (sum_a >= 1 ? "Yes" : "No") << endl;
    } else {
        vector<vector<int>> one_idxs_by_mod2(2);
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                one_idxs_by_mod2[i % 2].push_back(i);
            }
        }
        if (one_idxs_by_mod2[0].size() > 0 && one_idxs_by_mod2[1].size() > 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}