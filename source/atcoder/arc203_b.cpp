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
        vector<ll> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        ll a_sum = accumulate(a.begin(), a.end(), 0LL);
        ll b_sum = accumulate(b.begin(), b.end(), 0LL);
        if (a_sum != b_sum) {
            cout << "No\n";
        } else if (a_sum == 1 && b_sum == 1) {
            if ((a[0] == 1 || b[0] == 1 || a.back() == 1 || b.back() == 1) && a != b) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        } else {
            cout << "Yes\n";
        }
    }

    return 0;
}