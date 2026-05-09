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
    vector<array<int, 2>> tx(n);
    for (int i = 0; i < n; i++) {
        cin >> tx[i][0] >> tx[i][1];
    }

    vector<array<int, 2>> tx_trans(n);
    for (int i = 0; i < n; i++) {
        int t = tx[i][0];
        int x = tx[i][1];
        tx_trans[i][0] = t + x;
        tx_trans[i][1] = t - x;
    }

    sort(tx_trans.begin(), tx_trans.end(), [](auto &a, auto &b) {
        if (a[0] != b[0]) {
            return a[0] < b[0];
        }
        return a[1] < b[1];
    });

    vector<int> lis_stack;
    for (int i = 0; i < n; i++) {
        int cur = -tx_trans[i][1];
        auto it = lower_bound(lis_stack.begin(), lis_stack.end(), cur);
        if (it == lis_stack.end()) {
            lis_stack.push_back(cur);
        } else {
            *it = cur;
        }
    }

    cout << lis_stack.size();

    return 0;
}