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

    vector<int> lmis_stack;
    for (int i = 0; i < n; i++) {
        if (lmis_stack.empty() || lmis_stack.back() <= a[i]) {
            lmis_stack.push_back(a[i]);
        } else {
            auto it = upper_bound(lmis_stack.begin(), lmis_stack.end(), a[i]);
            *it = a[i];
        }
    }

    cout << n - (upper_bound(lmis_stack.begin(), lmis_stack.end(), a.back()) - lmis_stack.begin()) << "\n";

    return 0;
}