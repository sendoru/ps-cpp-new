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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        ll grundy = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            grundy ^= a[i];
        }
        grundy ^= (n + 1) % 2;
        if (grundy == 0) {
            cout << "tweede\n";
        } else {
            cout << "eerste\n";
        }
    }

    return 0;
}