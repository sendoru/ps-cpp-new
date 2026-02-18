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
    int ans;
    for (ans = 0; accumulate(a.begin(), a.end(), 0) > 0; ans++) {
        bool all_even = true;
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 1) {
                a[i]--;
                all_even = false;
                break;
            }
        }
        if (!all_even) {
            continue;
        }
        for (int i = 0; i < n; i++) {
            a[i] /= 2;
        }
    }
    cout << ans << "\n";

    return 0;
}